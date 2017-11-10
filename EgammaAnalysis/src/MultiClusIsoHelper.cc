#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "EgammaTools/EgammaAnalysis/interface/MultiClusIsoHelper.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "EgammaTools/EgammaAnalysis/interface/EgammaPCAHelper.h"
#include "RecoLocalCalo/HGCalRecAlgos/interface/HGCalImagingAlgo.h"

MultiClusIsoHelper::MultiClusIsoHelper():nlayers_(lastLayerFH),dr2_(0.15*0.15),mindr2_(0.03*0.03),ldr2_(0.03*0.03*1.2),radius_(3.){;}

MultiClusIsoHelper::MultiClusIsoHelper(float dr, float vetodr,size_t nrings):
    nlayers_(lastLayerFH),nrings_(nrings),dr2_(dr*dr), mindr2_(vetodr*vetodr),ldr2_(dr*dr*1.2),radius_(3.) {; }


MultiClusIsoHelper::~MultiClusIsoHelper(){}


int MultiClusIsoHelper::computeIso(const math::XYZPoint & pivot) {
    unsigned nclus = multiclusters_->size();
    float eta = pivot.eta();
    float phi = pivot.phi();
    float z = pivot.z();
    // reset
    setNRings(nrings_);
    for (unsigned iclus = 0; iclus < nclus ; ++ iclus) {
        // loose cleaning of multiclusters
        if (multiclusters_->at(iclus).z() * z < 0 ) continue;
        if (multiclusters_->at(iclus).hitsAndFractions()[0].first.det() != DetId::Forward ) continue;

        float deltar2=reco::deltaR2(eta,phi,multiclusters_->at(iclus).eta(),multiclusters_->at(iclus).phi());
        // use the loose cut
        if (deltar2 > ldr2_) continue;
        // now we have a cluster we can consider

        pcaHelper_.storeRecHits(multiclusters_->at(iclus));
        pcaHelper_.pcaInitialComputation();
        // first computation within cylinder, halo hits included
        pcaHelper_.computePCA(radius_);
        // second computation within cylinder, halo hits included
        if(!pcaHelper_.computePCA(radius_)) return 0;

        // computes the distance with the final position determination
        deltar2 = reco::deltaR2(eta,phi,pcaHelper_.barycenter().eta(),pcaHelper_.barycenter().phi());
        // apply the out cone and the veto cone
        if( deltar2 > dr2_ || deltar2 < mindr2_)
            continue;
        LongDeps ld(pcaHelper_.energyPerLayer(3.,true));
        for(unsigned ilayer = 1; ilayer < HGCalImagingAlgo::maxlayer+1; ++ilayer) {
            if(ilayer>=nlayers_) continue;
            size_t ring=ringasso_.at(ilayer);
            isoringdeposits_.at(ring) += ld.energyPerLayer()[ilayer];
        }

    }
    return 1;
}

// copied from HGCalIsoHelper
void MultiClusIsoHelper::setNRings(const size_t nrings){
    if(nrings>nlayers_)
        throw std::logic_error("MultiClusIsoHelper::setNRings: max number of rings reached");

    ringasso_.clear();
    isoringdeposits_.clear();
    size_t separator=nlayers_/nrings;
    size_t counter=0;
    for(size_t i=0;i<nlayers_+1;i++){
        ringasso_.push_back(counter);
        //the last ring might be larger.
        if(i && !(i%separator) && (int)counter<(int)nrings-1){
            counter++;
        }
    }
    isoringdeposits_.resize(nrings,0.);
}


float MultiClusIsoHelper::getIso(const size_t& ring)const{
    if(ring>=isoringdeposits_.size()) {
        throw std::out_of_range("MultiClusIsoHelper::getIso: ring index out of range");
    }
    return isoringdeposits_.at(ring);
}
