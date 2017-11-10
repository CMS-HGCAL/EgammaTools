#include "EgammaTools/EgammaAnalysis/interface/ElectronBDTHelper.h"

#include <iostream>
#include "TMath.h"

ElectronBDTHelper::ElectronBDTHelper(const edm::ParameterSet  & iConfig,edm::ConsumesCollector && iC):
ElectronsToken_(iC.consumes<edm::View<reco::GsfElectron>>(iConfig.getParameter<edm::InputTag>("GsfElectrons"))),
verticesToken_(iC.consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("vertices"))),
puSummaryInfoToken_(iC.consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("puSummary"))),
beamSpotToken_(iC.consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("beamSpot"))),
radius_(iConfig.getParameter<double>("pcaRadius")),
barrelLowPtFile_(iConfig.getParameter<std::string>("barrelLowPt")),
barrelHighPtFile_(iConfig.getParameter<std::string>("barrelHighPt")),
endcapLowPtFile_(iConfig.getParameter<std::string>("endcapLowPt")),
endcapHighPtFile_(iConfig.getParameter<std::string>("endcapHighPt")){

    barrelLowPtReader_= std::make_unique<TMVA::Reader>("!Color:!Silent");
    barrelHighPtReader_= std::make_unique<TMVA::Reader>("!Color:!Silent") ;
    endcapLowPtReader_= std::make_unique<TMVA::Reader>("!Color:!Silent");
    endcapHighPtReader_= std::make_unique<TMVA::Reader>("!Color:!Silent");

    initReader(*endcapLowPtReader_,endcapLowPtFile_);
    initReader(*endcapHighPtReader_,endcapHighPtFile_);
}

void ElectronBDTHelper::eventInit(const edm::Event& iEvent, const edm::EventSetup& iSetup){

    using namespace edm;

    Handle<edm::View<reco::GsfElectron>> ElectronsH;
    iEvent.getByToken(ElectronsToken_, ElectronsH);

    Handle<std::vector<reco::Vertex>> verticesHandle;
    iEvent.getByToken(verticesToken_, verticesHandle);
    auto const &vertices = *verticesHandle;
    tmva_Nvtx = vertices.size();

    Handle<std::vector<PileupSummaryInfo>>  puSIHandle;
    iEvent.getByToken(puSummaryInfoToken_,puSIHandle);
    auto const & pusi = *puSIHandle;
    unsigned npsi=pusi.size();
    int npu = 0;
    for (unsigned ipsi=0; ipsi<npsi ;++ ipsi) {
        if (pusi[ipsi].getBunchCrossing()==0) {
            npu = pusi[ipsi].getTrueNumInteractions();
            tmva_NPU = pusi[ipsi].getPU_NumInteractions();
            break;
        }
    }


    Handle<reco::BeamSpot> bsHandle;
    iEvent.getByToken(beamSpotToken_,bsHandle);
    auto const & beamspot = *bsHandle;

    float z_bs = beamspot.z0()*10.;
    float sigmaz_bs = beamspot.sigmaZ()*10.;
    tmva_PUdensity = puDensity(10.*vertices[0].z(), npu, z_bs, sigmaz_bs);
}

float ElectronBDTHelper::computeBDT(const reco::GsfElectron & electron) {
    tmva_ele_eta = electron.eta();
    tmva_ele_pT = electron.pt();
    tmva_ele_ET = electron.electronCluster()->energy() *std::sin(electron.theta());

    if(electron.isEB()) {
        // Fill some dummy value
        return -1.;
    }
    else {
        eIDHelper_->computeHGCAL(electron, radius_);

        // check the PCA has worked out
        if (eIDHelper_->sigmaUU() == -1){
            return -2.;
        }

        LongDeps ld(eIDHelper_->energyPerLayer(radius_, true));
        float measuredDepth, expectedDepth, expectedSigma;
        tmva_ele_hgc_depthCompat = eIDHelper_->clusterDepthCompatibility(ld, measuredDepth, expectedDepth, expectedSigma);

        // Fill here all the ValueMaps from their appropriate functions

        // Track-based
        tmva_ele_fbrem = electron.fbrem();
        tmva_ele_gsfhits = electron.gsfTrack()->hitPattern().trackerLayersWithMeasurement();
        tmva_ele_gsfchi2 = electron.gsfTrack()->normalizedChi2();

        reco::TrackRef myTrackRef = electron.closestCtfTrackRef();
        bool validKF = myTrackRef.isAvailable() && myTrackRef.isNonnull();
        tmva_ele_kfhits = (validKF) ? myTrackRef->hitPattern().trackerLayersWithMeasurement() : -1. ;
        tmva_ele_kfchi2 = (validKF) ? myTrackRef->normalizedChi2() : -1.;

        // Track-matching
        tmva_ele_eelepout = electron.eEleClusterOverPout();
        tmva_ele_deltaetaele = electron.deltaEtaEleClusterTrackAtCalo();
        tmva_ele_deltaphiele =  electron.deltaPhiEleClusterTrackAtCalo() ;

        // Cluster shapes
        // PCA related
        bool goodEle = eIDHelper_->sigmaVV()!=-1;
        tmva_ele_hgc_eigenvalues1 = (goodEle) ? eIDHelper_->eigenValues()(0) : -1.;
        tmva_ele_hgc_eigenvalues2 = (goodEle) ? eIDHelper_->eigenValues()(1) : -1.;
        tmva_ele_hgc_eigenvalues3 = (goodEle) ? eIDHelper_->eigenValues()(2) : -1.;

        tmva_ele_hgc_sigmas1 = (goodEle) ?  eIDHelper_->sigmas()(0) : -1. ;
        tmva_ele_hgc_sigmas2 = (goodEle) ?  eIDHelper_->sigmas()(1) : -1. ;
        tmva_ele_hgc_sigmas3 = (goodEle) ?  eIDHelper_->sigmas()(2) : -1. ;
        tmva_ele_hgc_pcaAxisX = (goodEle) ?  eIDHelper_->axis().x() : -1.;
        tmva_ele_hgc_pcaAxisY = (goodEle) ?  eIDHelper_->axis().y() : -1.;
        tmva_ele_hgc_pcaAxisZ = (goodEle) ?  eIDHelper_->axis().z() : -1.;
        tmva_ele_hgc_pcaPosX = (goodEle) ?  eIDHelper_->barycenter().x() : -1.;
        tmva_ele_hgc_pcaPosY = (goodEle) ?  eIDHelper_->barycenter().y() : -1.;
        tmva_ele_hgc_pcaPosZ = (goodEle) ?  eIDHelper_->barycenter().z() : -1.;

        // transverse shapes
        tmva_ele_sigmauu = eIDHelper_->sigmaUU();
        tmva_ele_sigmavv = eIDHelper_->sigmaVV();

        // long profile
        tmva_ele_hgc_nlay = ld.nLayers();
        tmva_ele_hgc_firstlay = ld.firstLayer();
        tmva_ele_hgc_lastlay = ld.lastLayer() ;
        tmva_ele_hgc_EE4overEE = ld.e4oEtot();
        tmva_ele_hgc_layEfrac10 = ld.layerEfrac10() ;
        tmva_ele_hgc_layEfrac90 = ld.layerEfrac90();

        //maps_["firstLayerEnergy"].push_back(ld.energyPerLayer()[ld.firstLayer()]);
        tmva_ele_hgc_FHoverEE = ( ld.energyEE() !=0.) ? ld.energyFH() / ld.energyEE() : -1.;
        // depth
        float bdt = (electron.pt() < 20. ) ? endcapLowPtReader_->EvaluateMVA("BDTSimpleCat") : endcapHighPtReader_->EvaluateMVA("BDTSimpleCat");
        return bdt;
    }
}

void ElectronBDTHelper::initReader(TMVA::Reader& reader, const std::string& file) {
   reader.AddVariable("ele_kfhits",&tmva_ele_kfhits);
   reader.AddVariable("ele_gsfhits",&tmva_ele_gsfhits);
   reader.AddVariable("ele_kfchi2",&tmva_ele_kfchi2);
   reader.AddVariable("ele_gsfchi2",&tmva_ele_gsfchi2);
   reader.AddVariable("ele_fbrem",&tmva_ele_fbrem);

   // E-p matching
   reader.AddVariable("ele_eelepout",&tmva_ele_eelepout);
   reader.AddVariable("ele_deltaetaele",&tmva_ele_deltaetaele);
   reader.AddVariable("ele_deltaphiele",&tmva_ele_deltaetaele);

   // Shower Shapes
    reader.AddVariable("ele_sigmauu",&tmva_ele_sigmauu);
    reader.AddVariable("ele_sigmavv",&tmva_ele_sigmavv);

    // HGC-specific
    reader.AddVariable("ele_hgc_eigenvalues1",&tmva_ele_hgc_eigenvalues1);
    reader.AddVariable("ele_hgc_eigenvalues2",&tmva_ele_hgc_eigenvalues2);
    reader.AddVariable("ele_hgc_eigenvalues3",&tmva_ele_hgc_eigenvalues3);
    reader.AddVariable("ele_hgc_sigmas1",&tmva_ele_hgc_sigmas1);
    reader.AddVariable("ele_hgc_sigmas2",&tmva_ele_hgc_sigmas2);
    reader.AddVariable("ele_hgc_sigmas3",&tmva_ele_hgc_sigmas3);
    reader.AddVariable("ele_hgc_pcaAxisX",&tmva_ele_hgc_pcaAxisX);
    reader.AddVariable("ele_hgc_pcaAxisY",&tmva_ele_hgc_pcaAxisY);
    reader.AddVariable("ele_hgc_pcaAxisZ",&tmva_ele_hgc_pcaAxisZ);
    reader.AddVariable("ele_hgc_pcaPosX",&tmva_ele_hgc_pcaPosX);
    reader.AddVariable("ele_hgc_pcaPosY",&tmva_ele_hgc_pcaPosY);
    reader.AddVariable("ele_hgc_pcaPosZ",&tmva_ele_hgc_pcaPosZ);
    reader.AddVariable("ele_hgc_FHoverEE",&tmva_ele_hgc_FHoverEE);
    reader.AddVariable("ele_hgc_nlay",&tmva_ele_hgc_nlay);
    reader.AddVariable("ele_hgc_firstlay",&tmva_ele_hgc_firstlay);
    reader.AddVariable("ele_hgc_lastlay",&tmva_ele_hgc_lastlay);
    reader.AddVariable("ele_hgc_EE4overEE",&tmva_ele_hgc_EE4overEE);
    reader.AddVariable("ele_hgc_layEfrac10",&tmva_ele_hgc_layEfrac10);
    reader.AddVariable("ele_hgc_layEfrac90",&tmva_ele_hgc_layEfrac90);
    reader.AddVariable("ele_hgc_depthCompat",&tmva_ele_hgc_depthCompat);
    reader.AddSpectator("ele_pT",&tmva_ele_pT);
    reader.AddSpectator("ele_eta",&tmva_ele_eta);
    reader.AddSpectator("Nvtx",&tmva_Nvtx);
    reader.AddSpectator("ele_ET",&tmva_ele_ET);
    reader.AddSpectator("NPU",&tmva_NPU);
    reader.AddSpectator("PU_density",&tmva_PUdensity);

    reader.BookMVA("BDTSimpleCat", file);

}

float ElectronBDTHelper::puDensity(float z, int npu, float z0,float sigmaz) const {
    float x = z-z0;
    return npu*std::exp(-0.5*x*x/sigmaz/sigmaz)/std::sqrt(2.*TMath::TwoPi())/sigmaz;
}
