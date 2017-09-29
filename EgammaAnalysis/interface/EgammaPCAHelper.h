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
    void storeRecHits(const reco::CaloCluster * theCluster );

    const TPrincipal & pcaResult();
    /// to set from outside - once per event
    void setHitMap(const std::map<DetId,const HGCARecHit *> * hitMap) ;
    /// to compute from inside - once per event
    void fillHitMap(const HGCRecHitCollection & HGCEERecHits);

    void setRecHitTools(const hgcal::RecHitTools * recHitTools );

    inline void setdEdXWeights(const std::vector<double> & dEdX){ dEdXWeights_ = dEdX;}

    void pcaInitialComputation() {
        computePCA(-1.,false);
    }

    void computePCA(float radius, bool withHalo=true);

    void computeShowerWidth(float radius, bool withHalo=true);

    inline double sigmaUU() const { return sigu_;}
    inline double sigmaVV() const { return sigv_;}
    inline double sigmaEE() const { return sige_;}
    inline double sigmaPP() const { return sigp_;}

private:

    bool recHitsStored_;
    int hitMapOrigin_; // 0 not initialized; 1 set from outside ; 2 set from inside
    std::unique_ptr<TPrincipal> pca_;
    const reco::CaloCluster * theCluster_
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
    Transform3D trans;
    double sigu_,sigv_,sige_,sigp_;
};

#endif
