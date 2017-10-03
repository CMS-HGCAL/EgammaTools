#include "EgammaTools/EgammaAnalysis/interface/ElectronIDHelper.h"

#include <iostream>

ElectronIDHelper::ElectronIDHelper(const edm::ParameterSet  & iConfig,edm::ConsumesCollector && iC):
        eeRecHitInputTag_(iConfig.getParameter<edm::InputTag> ("EERecHits") ),
        dEdXWeights_(iConfig.getParameter<std::vector<double> >("dEdXWeights")){
    recHitsEE_ = iC.consumes<HGCRecHitCollection>(eeRecHitInputTag_);
    pcaHelper_.setdEdXWeights(dEdXWeights_);
    debug_ = false;
}

void ElectronIDHelper::eventInit(const edm::Event& iEvent,const edm::EventSetup &iSetup) {
    edm::Handle<HGCRecHitCollection> recHitHandleEE;
    iEvent.getByToken(recHitsEE_, recHitHandleEE);

    pcaHelper_.fillHitMap(*recHitHandleEE);
    recHitTools_.getEventSetup(iSetup);

    pcaHelper_.setRecHitTools(&recHitTools_);
}

void ElectronIDHelper::computeHGCAL(const reco::GsfElectron & theElectron, float radius) {
    if (theElectron.isEB()) {
        if (debug_) std::cout << "The electron is in the barrel" <<std::endl;
        return;
    }

    pcaHelper_.storeRecHits(*theElectron.electronCluster());
    if (debug_)
        std::cout << " Stored the hits belonging to the electronCluster " << std::endl;

    pcaHelper_.pcaInitialComputation();
    pcaHelper_.computePCA(radius);
    pcaHelper_.computeShowerWidth(radius);
}
