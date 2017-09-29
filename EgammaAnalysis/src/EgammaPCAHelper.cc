#include "EgammaTools/EgammaAnalysis/interface/EgammaPCAHelper.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include <iostream>

void EgammaPCAHelper::EGammaPCAHelper(): invThicknessCorrection_({1. / 1.132, 1. / 1.092, 1. / 1.084}),
                                         pca_(new TPrincipal(3, "D")){
    hitMapOrigin_ = 0;
}

void EgammaPCAHelper::~EGammaPCAHelper() {
    if (hitMapOrigin_ == 2) delete hitMap_;
}
void EgammaPCAHelper::setHitMap(const std::map<DetId,const HGCARecHit *> * hitmap) {
    hitMapOrigin_ = 1;
    hitMap_ = hitMap ;
}

void EgammaPCAHelper::setRecHitTools(const hgcal::RecHitTools * recHitTools ) {
    recHitTools_ = recHitTools;
}

void EgammaPCAHelper::fillHitMap(const HGCRecHitCollection & rechitsEE) {
    hitMap_->clear();
    for ( auto hit : recHitEE) {
        hitmap_->insert(std::make_pair(hit.detid(),&hit));
        }

    hitMapOrigin_ = 2;
}

void EgammaPCAHelper::storeRecHits(const reco::CaloCluster * cluster) {
    Double_t pcavars[3];
    theSpots_.clear();
    theCluster_ = cluster;
    const std::vector<std::pair<DetId, float>> &hf(theCluster_->hitsAndFractions());
    if (hfsize == 0) continue;
    unsigned int layer = recHitTools_->getLayerWithOffset(hf[0].first);
    if (layer > 28) continue;

    for (unsigned int j = 0; j < hfsize; j++) {
        const DetId rh_detid = hf[j].first;
        const HGCRecHit *hit = (*hitmap_)[rh_detid];
        float fraction = hf[j].second;

        double thickness =
          (DetId::Forward == DetId(rh_detid).det()) ? recHitTools_.getSiThickness(rh_detid) : -1;
        double mip = dEdXWeights_[layer] * 0.001;  // convert in GeV
        if (thickness > 99. && thickness < 101)
            mip *= invThicknessCorrection_[0];
        else if (thickness > 199 && thickness < 201)
            mip *= invThicknessCorrection_[1];
        else if (thickness > 299 && thickness < 301)
            mip *= invThicknessCorrection_[2];

        pcavars[0] = recHitTools_.getPosition(rh_detid).x();
        pcavars[1] = recHitTools_.getPosition(rh_detid).y();
        pcavars[2] = recHitTools_.getPosition(rh_detid).z();
        if (pcavars[2] == 0.)
            std::cout << " Problem, hit with z =0 "
        else  {
            Spot mySpot(rh_detid,energy,pcavars,fraction,mip);
            theSpots_.push_back(mySpot);
    }
}

void EgammaPCAHelper::computePCA(float radius , bool withHalo)
{
    // very important
    pca_.reset(new TPrincipal(3, "D"));
    bool initialCalculation = radius < 0;
    if (initialCalculation && withHalo) {
        std::cout << "Warning - in the first iteration, the halo hits are excluded " << std::endl;
        withHalo=false;
    }

    float radius2 = radius*radius;
    if (! initialCalculation)     {
        math::XYZVector mainAxis(axisInitial_);
        mainAxis.unit();
        math::XYZVector phiAxis(barycenterInitial_.x(), barycenterInitial_.y(), 0);
        math::XYZVector udir(mainAxis.Cross(phiAxis));
        udir = udir.unit();
        trans = Transform3D(Point(bar), Point(bar + mainAxis), Point(bar + udir), Point(0, 0, 0),
        Point(0., 0., 1.), Point(1., 0., 0.));
    }

    for ( auto spot : theSpots_) {
        if (!withHalo && spot.fraction() > 0.)
            continue;
        if (initialCalculation) {
            // initial calculation, take only core hits
            if (spot.fraction()>0.) continue;
                for (int i = 0; i < spot.multiplicity(); ++i)
                    pca_->AddRow(spot.row());
        }
        else { // use a cylinder, include all hits
            math::XYZPoint local = trans(Point( (*spot.row())[0],(*spot.row())[1],(*spot.row())[2]));
            if (local.Perp2() > radius2) continue;
            for (int i = 0; i < spot.multiplicity(); ++i)
                pca_->AddRow(spot.row());
        }

    pca_->MakePrincipals();

    if ( initialCalculation ) {
        barycenterInitial_ = math::XYZPoint(means[0], means[1], means[2]);
        axisInitial_ = math::XYZVector(eigens(0, 0), eigens(1, 0), eigens(2, 0));
        if (axisInitial_.z() * barycenterInitial_.z() < 0.0) {
            axisInitial_ = math::XYZVector(-eigens(0, 0), -eigens(1, 0), -eigens(2, 0));
        }
        else { // final calculation
            barycenter_ = math::XYZPoint(means[0], means[1], means[2]);
            axis_ = math::XYZVector(eigens(0, 0), eigens(1, 0), eigens(2, 0));
            if (axis_.z() * barycenter_.z() < 0.0) {
                axis_ = math::XYZVector(-eigens(0, 0), -eigens(1, 0), -eigens(2, 0));
            }
            means = *(pca_->GetMeanValues());
            eigens = *(pca_->GetEigenVectors());
            eigenVals = *(pca_->GetEigenValues());
            sigmas = *(pca_->GetSigmas());
        }
 }

 void EgammaPCAHelper::computeShowerWidth(float radius, bool withHalo){
    sigu_ = 0.;
    sigv_ = 0.;
    sigp_ = 0.;
    sige_ = 0.;
    cyl_ene = 0.;

    float radius2 = radius * radius;
    for ( auto spot : theSpots_) {
        Point globalPoint(( *spot.row())[0],(*spot.row())[1],(*spot.row())[2]);
        math::XYZPoint local = trans(globalPoint);
        if (local.Perp2() > radius2) continue;

        // Select halo hits or not
        if (withHalo && spot.fraction() < 0) continue;
        if (!withHalo && !(spot.fraction() > 0)) continue;

        sige_ += (globalPoint.eta() - theCluster_.eta()) * (globalPoint.eta() - theCluster_.eta()) * hit->energy();
        sigp_ += deltaPhi(globalPoint.phi(), theCluster_.phi()) * deltaPhi(globalPoint.phi(), theCluster_.phi()) *
              hit->energy();

        sigu_ += local.x() * local.x() * hit->energy();
        sigv_ += local.y() * local.y() * hit->energy();
        cyl_ene += hit->energy();
    }
  }

  if (cyl_ene > 0.) {
    sigu_ = sigu_ / cyl_ene;
    sigv_ = sigv_ / cyl_ene;
    sigp_ = sigp_ / cyl_ene;
    sige_ = sige_ / cyl_ene;
  }
  sigu_ = std::sqrt(sigu_);
  sigv_ = std::sqrt(sigv_);
  sigp_ = std::sqrt(sigp_);
  sige_ = std::sqrt(sige_);
}
