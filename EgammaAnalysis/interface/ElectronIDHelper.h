//--------------------------------------------------------------------------------------------------
//
// EGammaID Helper
//
// Helper Class to compute electron ID observables
//
// Authors: F. Beaudette,A. Lobanov
//--------------------------------------------------------------------------------------------------

#ifndef ElectronIDHelper_H
#define ElectronIDHelper_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/HGCRecHit/interface/HGCRecHitCollections.h"

#include "EgammaTools/EgammaAnalysis/interface/EgammaPCAHelper.h"
#include <vector>

class ElectronIDHelper {
public:
    ElectronIDHelper(){;}
    ElectronIDHelper(const edm::InputTag &, edm::ConsumesCollector & iC);
    ~ElectronIDHelper(){;}
    // to be run once per event
    void eventInit(const edm::Event& iEvent,const edm::EventSetup &iSetup);

    void computeHGCAL(const reco::GsfElectron & theElectron);

private:
    edm::InputTag  eeRecHitInputTag_;
    EGammaPCAHelper pcaHelper_;
    edm::EDGetTokenT<HGCRecHitCollection> recHitsEE_;
    hgcal::RecHitTools recHitTools_;
};

#endif
