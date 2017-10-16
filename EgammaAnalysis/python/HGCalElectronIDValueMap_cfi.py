import FWCore.ParameterSet.Config as cms
from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import dEdX_weights as dEdX

HGCalElectronIDValueMap = cms.EDProducer("HGCalElectronIDValueMapProducer",
    electrons = cms.InputTag("ecalDrivenGsfElectronsFromMultiCl"),
    pcaRadius = cms.double(3.),
    EERecHits = cms.InputTag('HGCalRecHit:HGCEERecHits'),
    FHRecHits = cms.InputTag('HGCalRecHit:HGCHEFRecHits'),
    BHRecHits = cms.InputTag('HGCalRecHit:HGCHEBRecHits'),
    dEdXWeights = dEdX,
)
