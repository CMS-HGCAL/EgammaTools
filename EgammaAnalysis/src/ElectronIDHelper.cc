#include "EgammaTools/EgammaAnalysis/interface/ElectronIDHelper.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"

#include <iostream>

ElectronIDHelper::ElectronIDHelper(const edm::ParameterSet  & iConfig,edm::ConsumesCollector && iC):
        eeRecHitInputTag_(iConfig.getParameter<edm::InputTag> ("EERecHits") ),
        fhRecHitInputTag_(iConfig.getParameter<edm::InputTag> ("FHRecHits") ),
        bhRecHitInputTag_(iConfig.getParameter<edm::InputTag> ("BHRecHits") ),
        dEdXWeights_(iConfig.getParameter<std::vector<double> >("dEdXWeights")){
    recHitsEE_ = iC.consumes<HGCRecHitCollection>(eeRecHitInputTag_);
    recHitsFH_ = iC.consumes<HGCRecHitCollection>(fhRecHitInputTag_);
    recHitsBH_ = iC.consumes<HGCRecHitCollection>(bhRecHitInputTag_);
    pcaHelper_.setdEdXWeights(dEdXWeights_);
    debug_ = false;
}

void ElectronIDHelper::eventInit(const edm::Event& iEvent,const edm::EventSetup &iSetup) {
    edm::Handle<HGCRecHitCollection> recHitHandleEE;
    iEvent.getByToken(recHitsEE_, recHitHandleEE);
    edm::Handle<HGCRecHitCollection> recHitHandleFH;
    iEvent.getByToken(recHitsFH_, recHitHandleFH);
    edm::Handle<HGCRecHitCollection> recHitHandleBH;
    iEvent.getByToken(recHitsBH_, recHitHandleBH);

    pcaHelper_.fillHitMap(*recHitHandleEE,*recHitHandleFH,*recHitHandleBH);
    recHitTools_.getEventSetup(iSetup);
    pcaHelper_.setRecHitTools(&recHitTools_);
}

void ElectronIDHelper::setRecHitTools(const hgcal::RecHitTools * recHitTools){
    pcaHelper_.setRecHitTools(recHitTools);
}

void ElectronIDHelper::computeHGCAL(const reco::GsfElectron & theElectron, float radius) {
    theElectron_ = &theElectron;
    if (theElectron.isEB()) {
        if (debug_) std::cout << "The electron is in the barrel" <<std::endl;
        pcaHelper_.clear();
        return;
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
    pcaHelper_.computePCA(radius);
    pcaHelper_.computeShowerWidth(radius);
}

void ElectronIDHelper::computeHGCAL(const reco::Photon & thePhoton, float radius) {
    if (thePhoton.isEB()) {
        if (debug_) std::cout << "The electron is in the barrel" <<std::endl;
        pcaHelper_.clear();
        return;
    }

    pcaHelper_.storeRecHits(*thePhoton.superCluster()->seed());
    if (debug_)
        std::cout << " Stored the hits belonging to the photonCluster " << std::endl;

    // initial computation, no radius cut, but halo hits not taken
    if (debug_)
        std::cout << " Calling PCA initial computation" << std::endl;
    pcaHelper_.pcaInitialComputation();
    // first computation within cylinder, halo hits included
    pcaHelper_.computePCA(radius);
    // second computation within cylinder, halo hits included
    pcaHelper_.computePCA(radius);
    pcaHelper_.computeShowerWidth(radius);
}
