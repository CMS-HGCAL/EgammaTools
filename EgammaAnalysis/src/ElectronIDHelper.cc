#include "EgammaTools/EgammaAnalysis/interface/ElectronIDHelper.h"

#include <iostream>

ElectronIDHelper::ElectronIDHelper(const edm::ParameterSet  & iConfig,edm::ConsumesCollector && iC):
                                eeRecHitInputTag_(iConfig.getParameter<edm::InputTag> ("EERecHits") ),
                                fhRecHitInputTag_(iConfig.getParameter<edm::InputTag> ("FHRecHits") ),
                                bhRecHitInputTag_(iConfig.getParameter<edm::InputTag> ("BHRecHits") ),
                                multiclusterTag_(iConfig.getParameter<edm::InputTag> ("PFMultiClusters") ),
                                dEdXWeights_(iConfig.getParameter<std::vector<double> >("dEdXWeights") )
{

    isoHelper_.setDeltaR(iConfig.getUntrackedParameter<double>("electronIsoDeltaR", 0.15));
    isoHelper_.setNRings(iConfig.getUntrackedParameter<int>("electronIsoNRings", 5));
    isoHelper_.setMinDeltaR(iConfig.getUntrackedParameter<double>("electronIsoDeltaRmin", 0.));

    recHitsEE_ = iC.consumes<HGCRecHitCollection>(eeRecHitInputTag_);
    recHitsFH_ = iC.consumes<HGCRecHitCollection>(fhRecHitInputTag_);
    recHitsBH_ = iC.consumes<HGCRecHitCollection>(bhRecHitInputTag_);
    multiClusters_ = iC.consumes<std::vector<reco::PFCluster>>(multiclusterTag_);
    pcaHelper_.setdEdXWeights(dEdXWeights_);
    debug_ = false;
    multiclusIsoHelper_ = new MultiClusIsoHelper(0.15, 0.03,7);
    multiclusIsoHelper_->setdEdXWeights(dEdXWeights_);
}

ElectronIDHelper::~ElectronIDHelper() { delete multiclusIsoHelper_;}

void ElectronIDHelper::eventInit(const edm::Event& iEvent,const edm::EventSetup &iSetup) {
    edm::Handle<HGCRecHitCollection> recHitHandleEE;
    iEvent.getByToken(recHitsEE_, recHitHandleEE);
    edm::Handle<HGCRecHitCollection> recHitHandleFH;
    iEvent.getByToken(recHitsFH_, recHitHandleFH);
    edm::Handle<HGCRecHitCollection> recHitHandleBH;
    iEvent.getByToken(recHitsBH_, recHitHandleBH);
    edm::Handle<std::vector<reco::PFCluster>> clusterHandle;
    iEvent.getByToken(multiClusters_, clusterHandle);

    pcaHelper_.fillHitMap(*recHitHandleEE,*recHitHandleFH,*recHitHandleBH);
    isoHelper_.setHitMap(pcaHelper_.getHitMap());
    multiclusIsoHelper_->setHitMap(pcaHelper_.getHitMap());
    recHitTools_.getEventSetup(iSetup);
    pcaHelper_.setRecHitTools(&recHitTools_);
    isoHelper_.setRecHitTools(&recHitTools_);
    multiclusIsoHelper_->setRecHitTools(&recHitTools_);
    multiclusIsoHelper_->setIsoClusterCollection(&(*clusterHandle));
}

void ElectronIDHelper::setRecHitTools(const hgcal::RecHitTools * recHitTools){
    pcaHelper_.setRecHitTools(recHitTools);
}

float ElectronIDHelper::getIsolationRing(size_t ring) const {
    if (isomethod_==1)  return isoHelper_.getIso(ring);
        else if (isomethod_==2) return multiclusIsoHelper_->getIso(ring);
    return -1.;
}

int ElectronIDHelper::computeHGCAL(const reco::GsfElectron & theElectron, float radius, int isomethod) {
    theElectron_ = &theElectron;
    isomethod_ = isomethod;
    if (theElectron.isEB()) {
        if (debug_) std::cout << "The electron is in the barrel" <<std::endl;
        pcaHelper_.clear();
        return 0;
    }

    pcaHelper_.storeRecHits(*theElectron.electronCluster());
    if (debug_)
        std::cout << " Stored the hits belonging to the electronCluster " << std::endl;

    // initial computation, no radius cut, but halo hits not taken
    if (debug_)
        std::cout << " Calling PCA initial computation" << std::endl;
    pcaHelper_.pcaInitialComputation();
    // first computation within cylinder, halo hits included
    pcaHelper_.computePCA(radius);
    // second computation within cylinder, halo hits included
    if(!pcaHelper_.computePCA(radius)) return 0;

    pcaHelper_.computeShowerWidth(radius);

    if(isomethod_==1)
        isoHelper_.produceHGCalIso(theElectron.electronCluster());
    else if (isomethod_==2) {
            multiclusIsoHelper_->setNRings(7);
            multiclusIsoHelper_->computeIso(pcaHelper_.barycenter());
        }
    return 1;

}
