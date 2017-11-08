/*
 * MultiClusIsoHelper.h
 *
 *  Created on: 27 Oct 2017
 *      Author: F. Beaudette
 */

#ifndef EGAMMATOOL_EGAMMAANALYSIS_MULTICLUSISOHELPER_H_
#define EGAMMATOOL_EGAMMAANALYSIS_MULTICLUSISOHELPER_H_
#include "DataFormats/ParticleFlowReco/interface/HGCalMultiCluster.h"
#include "DataFormats/HGCRecHit/interface/HGCRecHitCollections.h"
#include "EgammaTools/EgammaAnalysis/interface/EgammaPCAHelper.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"

class MultiClusIsoHelper{
 public:
     MultiClusIsoHelper(float dr, float vetodr, size_t nrings=7);
     MultiClusIsoHelper();
     inline void setHitMap( std::map<DetId,const HGCRecHit *> * hitMap) {pcaHelper_.setHitMap(hitMap);}
     inline void setRecHitTools(const hgcal::RecHitTools * recHitTools){
         pcaHelper_.setRecHitTools(recHitTools);
     }
     void setNRings(const size_t nrings);
     inline void setIsoClusterCollection(const std::vector<reco::PFCluster> *multiclusters) {multiclusters_= multiclusters;}
     int computeIso(const math::XYZPoint & pivot);
     inline void setdEdXWeights(const std::vector<double> & dEdX){ pcaHelper_.setdEdXWeights(dEdX);}
     float getIso(const size_t& ring) const;
     ~MultiClusIsoHelper();

 private:
     math::XYZPoint pivot_;
     std::vector<float> isoringdeposits_;
     size_t nlayers_;
     size_t nrings_;
     float dr2_, mindr2_, ldr2_;
     float radius_;

     EGammaPCAHelper pcaHelper_;
     std::map<DetId, const HGCRecHit *> * allHitMap_;
     std::vector<size_t> ringasso_;
     static const unsigned int lastLayerFH = 40;
     const std::vector<reco::PFCluster> * multiclusters_;
};

 #endif
