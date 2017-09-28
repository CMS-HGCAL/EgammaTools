#include "EgammaTools/EgammaAnalysis/interface/EgammaPCAHelper.h"

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

void EgammaPCAHelper::storeRecHits(const reco::CaloCluster & theCluster) {
    Double_t pcavars[3];
    theSpots_.clear();

    const std::vector<std::pair<DetId, float>> &hf(layerCluster->hitsAndFractions());
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

        Spot mySpot(rh_detid,energy,pcavars,fraction,mip);
        theSpots_.push_back(mySpot);
}

void EgammaPCAHelper::computePCA(float radius , bool excludeHalo)
{
     pca_.reset(new TPrincipal(3, "D"));

     for ( auto hit : recHitEE) {    

     pca_->MakePrincipals();
}
