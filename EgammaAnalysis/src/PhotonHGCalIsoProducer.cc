/*
 * PhotonIsoProducer.cc
 *
 *  Created on: 13 Oct 2017
 *      Author: jkiesele
 */

#include "EgammaTools/EgammaAnalysis/interface/PhotonHGCalIsoProducer.h"
#include <stdexcept>

PhotonHGCalIsoProducer::PhotonHGCalIsoProducer():dr_(0.15),mindr_(0),rechittools_(0),debug_(false){

    allHitMap_ = new std::map<DetId, const HGCRecHit *>();
    setNRings(5);
}

void PhotonHGCalIsoProducer::produceHGCalIso(const reco::Photon& photon){

    if(!rechittools_)
        throw std::runtime_error("PhotonHGCalIsoProducer::produceCaloIso: rechittools not set");

    for(auto& r:isoringdeposits_)
        r=0;

    //this could be replaced by the hit map created by storeRecHits in PCAhelpers
    std::vector<DetId>photonhits;
    const std::vector<std::pair<DetId,float > > & photonhitmap= photon.superCluster()->seed()->hitsAndFractions();
    for(const auto& h:photonhitmap)
        photonhits.push_back(h.first);

    for(const auto& hit: *allHitMap_) {

        const GlobalPoint position = rechittools_->getPosition(hit.first);
        float eta=rechittools_->getEta(position, 0);//assume vertex at z=0
        float phi=rechittools_->getPhi(position);
        float deltar=reco::deltaR(eta,phi,photon.eta(),photon.phi());

        if(deltar>dr_ || deltar<mindr_) continue;

        size_t layer=rechittools_->getLayerWithOffset(hit.first);
        if(layer>=nlayers) continue;

        const size_t& ring=ringasso_.at(layer);

        //do not consider hits associated to the photon cluster
        if(std::find(photonhits.begin(),photonhits.end(),hit.first)==photonhits.end()){
            isoringdeposits_.at(ring)+=hit.second->energy();
        }
    }

    //does this make sense here or should it be done later?
    for(size_t i=0;i<isoringdeposits_.size();i++){
        isoringdeposits_.at(i)/=photon.energy();
    }
}

void PhotonHGCalIsoProducer::setNRings(const size_t nrings){
    if(nrings>nlayers)
        throw std::logic_error("PhotonHGCalIsoProducer::setNRings: max number of rings reached");

    ringasso_.clear();
    isoringdeposits_.clear();
    size_t separator=nlayers/nrings;
    size_t counter=0;
    for(size_t i=0;i<nlayers+1;i++){
        ringasso_.push_back(counter);
        //the last ring might be larger.
        if(i && !(i%separator) && (int)counter<(int)nrings-1){
            counter++;
        }
    }
    isoringdeposits_.resize(nrings,0);
}

//copied from electronIDProducer - can be merged
void PhotonHGCalIsoProducer::fillHitMap(const HGCRecHitCollection & rechitsEE,
                                 const HGCRecHitCollection & rechitsFH,
                                 const HGCRecHitCollection & rechitsBH) {
    allHitMap_->clear();
    unsigned hitsize = rechitsEE.size();
    for ( unsigned i=0; i< hitsize ; ++i) {
        (*allHitMap_)[rechitsEE[i].detid()] = & rechitsEE[i];
    }

    if (debug_)
        std::cout << " EE " << hitsize << " RecHits " << std::endl;
    hitsize = rechitsFH.size();
    for ( unsigned i=0; i< hitsize ; ++i) {
        (*allHitMap_)[rechitsFH[i].detid()] = & rechitsFH[i];
    }
    if (debug_)
        std::cout << " FH " << hitsize << " RecHits " << std::endl;
    hitsize = rechitsBH.size();
    for ( unsigned i=0; i< hitsize ; ++i) {
        (*allHitMap_)[rechitsBH[i].detid()] = & rechitsBH[i];
    }
    if (debug_)
        std::cout << " BH " << hitsize << " RecHits " << std::endl;
    if( debug_)
        std::cout << " Stored " << allHitMap_->size() << " rechits " << std::endl;

}

const float& PhotonHGCalIsoProducer::getIso(const size_t& ring)const{
    if(ring>=isoringdeposits_.size())
        throw std::out_of_range("PhotonHGCalIsoProducer::getIso: ring index out of range");
    return isoringdeposits_.at(ring);
}
