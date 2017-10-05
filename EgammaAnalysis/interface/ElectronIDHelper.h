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
#include "FWCore/ParameterSet/interface/ParameterSet.h"


#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/HGCRecHit/interface/HGCRecHitCollections.h"

#include "EgammaTools/EgammaAnalysis/interface/EgammaPCAHelper.h"
#include <vector>

class ElectronIDHelper {
public:
    ElectronIDHelper(){;}
    ElectronIDHelper(const edm::ParameterSet &, edm::ConsumesCollector && iC);
    ~ElectronIDHelper(){;}
    // to be run once per event
    void eventInit(const edm::Event& iEvent,const edm::EventSetup &iSetup);

    void computeHGCAL(const reco::GsfElectron & theElectron, float radius);

    inline double sigmaUU() const {  return pcaHelper_.sigmaUU();}
    inline double sigmaVV() const {  return pcaHelper_.sigmaVV();}
    inline double sigmaEE() const {  return pcaHelper_.sigmaEE();}
    inline double sigmaPP() const {  return pcaHelper_.sigmaPP();}

    inline unsigned nLayers() const { return pcaHelper_.layersCrossed().size();}
    inline int firstLayer() const { return (nLayers()>0) ? *pcaHelper_.layersCrossed().begin() : -1 ;}
    inline int lastLayer() const { return (nLayers()>0) ? *pcaHelper_.layersCrossed().rbegin() : -1 ;}

private:
    edm::InputTag  eeRecHitInputTag_;
    edm::InputTag  fhRecHitInputTag_;
    edm::InputTag  bhRecHitInputTag_;

    std::vector<double> dEdXWeights_;
    EGammaPCAHelper pcaHelper_;
    edm::EDGetTokenT<HGCRecHitCollection> recHitsEE_;
    edm::EDGetTokenT<HGCRecHitCollection> recHitsFH_;
    edm::EDGetTokenT<HGCRecHitCollection> recHitsBH_;
    hgcal::RecHitTools recHitTools_;
    bool debug_;
};

#endif
