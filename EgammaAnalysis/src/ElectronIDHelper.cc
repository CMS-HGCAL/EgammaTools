#include "EgammaTools/EgammaAnalysis/interface/ElectronIDHelper.h"

ElectronIDHelper::ElectronIDHelper(const edm::InputTag & eeRecHitInputTag,edm::ConsumesCollector & iC):eeRecHitInputTag_(eeRecHitInputTag){
    recHitsEE_ = iC.consumes<HGCRecHitCollection>(eeRecHitInputTag);
}

void ElectronIDHelper::eventInit(const edm::Event& iEvent,const edm::EventSetup &iSetup) {
    edm::Handle<HGCRecHitCollection> recHitHandleEE;
    iEvent.getByToken(recHitsEE_, recHitHandleEE);

    pcaHelper_.fillHitMap(*recHitHandleEE);
    recHitTools_.getEventSetup(iSetup);

    pcaHelper_.setRecHitTools(&recHitTools_);
}

void ElectronIDHelper::computeHGCAL(const reco::GsfElectron & theElectron) {
    pcaHelper_.storeRecHits(*theElectron.electronCluster());
}
