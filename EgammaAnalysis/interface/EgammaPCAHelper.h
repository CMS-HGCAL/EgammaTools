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
#include "DataFormats/Math/interface/Vector3D.h"

#include "EgammaTools/EgammaAnalysis/interface/Spot.h"
#include "RecoLocalCalo/HGCalRecAlgos/interface/RecHitTools.h"
#include "FastSimulation/CaloGeometryTools/interface/Transform3DPJ.h"
#include <map>

#include "TPrincipal.h"

class HGCalRecHit;

class EGammaPCAHelper
{
public:
    typedef ROOT::Math::Transform3DPJ Transform3D;
    typedef ROOT::Math::Transform3DPJ::Point Point;

    EGammaPCAHelper();
    ~EGammaPCAHelper();

    // for the GsfElectrons
    void storeRecHits(const reco::CaloCluster & theCluster );

    const TPrincipal & pcaResult();
    /// to set from outside - once per event
    void setHitMap( std::map<DetId,const HGCRecHit *> * hitMap) ;
    /// to compute from inside - once per event
    void fillHitMap(const HGCRecHitCollection & HGCEERecHits);

    void setRecHitTools(const hgcal::RecHitTools * recHitTools );

    inline void setdEdXWeights(const std::vector<double> & dEdX){ dEdXWeights_ = dEdX;}

    void pcaInitialComputation() {
        computePCA(-1.,false);
    }

    void computePCA(float radius, bool withHalo=true);

    void computeShowerWidth(float radius, bool withHalo=true);

    inline double sigmaUU() const { checkIteration() ; return sigu_;}
    inline double sigmaVV() const { checkIteration() ; return sigv_;}
    inline double sigmaEE() const { checkIteration() ; return sige_;}
    inline double sigmaPP() const { checkIteration() ; return sigp_;}

private:
    void checkIteration() const ;

private:
    bool recHitsStored_;

    //parameters
    std::vector<double> dEdXWeights_;
    std::vector<double> invThicknessCorrection_;

    int hitMapOrigin_; // 0 not initialized; 1 set from outside ; 2 set from inside
    const reco::CaloCluster * theCluster_;
    std::map<DetId, const HGCRecHit *> * hitMap_;
    std::vector<Spot> theSpots_;
    unsigned pcaIteration_;

    // output quantities
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

    // helper
    std::unique_ptr<TPrincipal> pca_;
    const hgcal::RecHitTools * recHitTools_;

};

#endif
