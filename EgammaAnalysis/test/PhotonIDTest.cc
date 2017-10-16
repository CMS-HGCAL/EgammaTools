#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "EgammaTools/EgammaAnalysis/interface/PhotonIDHelper.h"
#include "EgammaTools/EgammaAnalysis/interface/LongDeps.h"

#include <iostream>
#include <iomanip>

class PhotonIdTest : public edm::one::EDAnalyzer<edm::one::WatchRuns, edm::one::SharedResources> {

public:

    PhotonIdTest();
    explicit PhotonIdTest(const edm::ParameterSet &);
    ~PhotonIdTest();

    virtual void beginRun(edm::Run const &iEvent, edm::EventSetup const &) override;
    virtual void endRun(edm::Run const &iEvent, edm::EventSetup const &) override;

private:
     virtual void analyze(const edm::Event &, const edm::EventSetup &) override;

private:
     PhotonIDHelper * pIDHelper_;
     edm::InputTag photonTag_;
     edm::EDGetTokenT<std::vector<reco::Photon>> photons_;
};

PhotonIdTest::PhotonIdTest(){;}

PhotonIdTest::~PhotonIdTest(){;}

PhotonIdTest::PhotonIdTest(const edm::ParameterSet &iConfig)
{
    pIDHelper_ = new PhotonIDHelper(iConfig ,consumesCollector());
    photonTag_ = iConfig.getParameter<edm::InputTag>("Photons");
    photons_ = consumes<std::vector<reco::Photon>>(photonTag_);
}

void PhotonIdTest::beginRun(edm::Run const &iEvent, edm::EventSetup const &) {;}

void PhotonIdTest::endRun(edm::Run const &iEvent, edm::EventSetup const &) {;}

void PhotonIdTest::analyze(const edm::Event &iEvent, const edm::EventSetup &iSetup) {
    pIDHelper_->eventInit(iEvent,iSetup);

    edm::Handle<std::vector<reco::Photon>> phoHandle;
    iEvent.getByToken(photons_, phoHandle);
    for (auto photon : *phoHandle) {
        std::cout << " Photon eta pt" << photon.eta() << " " << photon.pt() << std::endl;
        if (photon.isEB()) continue;
        pIDHelper_->computeHGCAL(photon,3.);
        std::cout << "sigmaUU " << pIDHelper_->sigmaUU() << std::endl;
        std::cout << "sigmaVV " << pIDHelper_->sigmaVV() << std::endl;
        std::cout << "sigmaEE " << pIDHelper_->sigmaEE() << std::endl;
        std::cout << "sigmaPP " << pIDHelper_->sigmaPP() << std::endl;

        LongDeps ld(pIDHelper_->energyPerLayer(3.,true));
        std::cout << "Nlayers " << ld.nLayers() << std::endl;

	//    std::cout << "GSF pt " << std::sqrt(photon.trackMomentumAtVtx().perp2()) << " " << photon.photonCluster()->energy() << std::endl;
    //   std::cout << photon.photonCluster()->size() << " " << photon.photonCluster()->hitsAndFractions().size() << std::endl;
    //   pIDHelper_->printHits(3.);

        std::cout << "First layer " << ld.firstLayer() << std::endl;
        std::cout << "Last layer " << ld.lastLayer() << std::endl;

        for (unsigned l=1;l<=52;++l) {
            std::cout << std::fixed << std::setw( 5 ) << std::setprecision( 2 ) << ld.energyPerLayer()[l] << " " ;
        }
        std::cout << std::endl;
        std::cout << " Energy EE " << ld.energyEE() << " EnergyFH " << ld.energyFH() << " EnergyBH " << ld.energyBH() <<std::endl;

        float measuredDepth, expectedDepth, expectedSigma;
        float depthCompatibility = pIDHelper_->clusterDepthCompatibility(ld,measuredDepth,expectedDepth, expectedSigma);
        std::cout << " Depth " << measuredDepth << " Exp. Depth " << expectedDepth << " ";
        std::cout << "Exp. Sigma " << expectedSigma <<  " Depth compatibility " <<depthCompatibility << std::endl;
    }

}

// define this as a plug-in
DEFINE_FWK_MODULE(PhotonIdTest);
