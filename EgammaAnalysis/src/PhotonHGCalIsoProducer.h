/*
 * PhotonIsoProducer.h
 *
 *  Created on: 13 Oct 2017
 *      Author: jkiesele
 */

#ifndef RECONTUPLES_HGCALANALYSIS_PLUGINS_PHOTONHGCALISOPRODUCER_H_
#define RECONTUPLES_HGCALANALYSIS_PLUGINS_PHOTONHGCALISOPRODUCER_H_

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/HGCRecHit/interface/HGCRecHitCollections.h"
#include "RecoLocalCalo/HGCalRecAlgos/interface/RecHitTools.h"


/*
 *
 * This class calculates the energy around the photon in DR=0.15 that is
 * not associated to the seed cluster of the photon.
 * The energy is summed in 5 rings (default) between HGCal layer 1 and 30 and normalised to
 * the total photon energy.
 * This gives back 5 calorimeter isolation values.
 * Only the first values should be significantly affected by pileup.
 *
 * Usage:
 *
 * PhotonHGCalIsoProducer prod;
 * prod.setRecHitTools(rechittools)
 * prod.fillHitMap(recHitsEE,recHitsFH,recHitsBH)
 *
 * <optional>
 * prod.setDeltaR(0.15)
 * <optional>
 * prod.setNRings(5)
 * <optional>
 * prod.setMinDeltaR(0)
 *
 * for p in photons
 *   prod.produceHGCalIso(p)
 *   a=prod.getIso(0)
 *   b=prod.getIso(1)
 *   c=prod.getIso(2)
 *   d=prod.getIso(3)
 *   e=prod.getIso(4)
 *
 *
 */
class PhotonHGCalIsoProducer{
public:
    PhotonHGCalIsoProducer();

    ~PhotonHGCalIsoProducer(){delete allHitMap_;}

    void setDeltaR(const float& dr){dr_=dr;}

    void setMinDeltaR(const float& dr){mindr_=dr;}

    void setRecHitTools(const hgcal::RecHitTools * recHitTools){rechittools_ = recHitTools;}

    void setNRings(const size_t nrings);

    void fillHitMap(const HGCRecHitCollection & rechitsEE,
            const HGCRecHitCollection & rechitsFH,
            const HGCRecHitCollection & rechitsBH);

    void produceHGCalIso(const reco::Photon& photon);

    const float& getIso(const size_t& ring)const;

private:
    std::vector<float> isoringdeposits_;
    std::vector<size_t> ringasso_;

    float dr_,mindr_;

    const hgcal::RecHitTools* rechittools_;
    std::map<DetId, const HGCRecHit *> * allHitMap_;

    bool debug_;
    static constexpr size_t nlayers=30;
};


#endif /* RECONTUPLES_HGCALANALYSIS_PLUGINS_PHOTONHGCALISOPRODUCER_H_ */
