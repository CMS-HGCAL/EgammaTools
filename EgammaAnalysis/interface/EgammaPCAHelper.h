//--------------------------------------------------------------------------------------------------
//
// EGammaPCAHelper
//
// Helper Class to compute PCA
//
//
//--------------------------------------------------------------------------------------------------
#ifndef EGammaPCAHelper_H
#define EGammaPCAHelper_H

#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/HGCRecHit/interface/HGCRecHitCollections.h"
#include "DataFormats/ForwardDetId/interface/HGCalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"

#include "RecoLocalCalo/HGCalRecAlgos/interface/RecHitTools.h"
#include "EgammaTools/EgammaAnalysis/interface/Spot.h"
#include "FastSimulation/CaloGeometryTools/interface/Transform3DPJ.h"
#include <map>

#include "TPrincipal.h"



class EGammaPCAHelper
{
public:
    typedef ROOT::Math::Transform3DPJ Transform3D;
    typedef ROOT::Math::Transform3DPJ::Point Point;
    
    void EGammaPCAHelper();
    void ~EGammaPCAHelper();

    // for the GsfElectrons
    void storeRecHits(const reco::CaloCluster & theCluster );

    const TPrincipal & pcaResult();
    /// to set from outside
    void setHitMap(const std::map<DetId,const HGCARecHit *> * hitMap) ;
  /// to compute from inside

    void setRecHitTools(const hgcal::RecHitTools * recHitTools );

    inline void setdEdXWeights(const std::vector<double> & dEdX){ dEdXWeights_ = dEdX;}

    void fillHitMap(const HGCRecHitCollection & HGCEERecHits);

    void pcaInitialComputation() {
        computePCA(-1.,false);
    }

    void computePCA(float radius , bool excludeHalo);

private:
    bool recHitsStored_;
    int hitMapOrigin_; // 0 not initialized; 1 set from outside ; 2 set from inside
    std::unique_ptr<TPrincipal> pca_;
    const std::map<DetId, const HGCRecHit *> * hitMap_;
    std::vector<double> dEdXWeights_;
    std::vector<double> invThicknessCorrection_;
    const hgcal::RecHitTools * recHitTools_
    std::vector<Spot> theSpots_;
    math::XYZPoint barycenterInitial_;
    math::XYZVector axisInitial_;
    math::XYZPoint barycenter_;
    math::XYZVector axis_;
    TVectorD means ;
    TMatrixD eigens ;
    TVectorD eigenVals ;
    TVectorD sigmas ;
};

#endif
