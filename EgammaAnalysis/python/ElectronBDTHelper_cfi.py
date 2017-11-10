import FWCore.ParameterSet.Config as cms
from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import dEdX_weights as dEdX

HGCalElectronIDValueMap = cms.EDProducer("HGCalElectronIDValueMapProducer",
    electrons = cms.InputTag("ecalDrivenGsfElectronsFromMultiCl"),
    pcaRadius = cms.double(3.),
    EERecHits = cms.InputTag('HGCalRecHit:HGCEERecHits'),
    FHRecHits = cms.InputTag('HGCalRecHit:HGCHEFRecHits'),
    BHRecHits = cms.InputTag('HGCalRecHit:HGCHEBRecHits'),
    vertices = cms.InputTag("offlinePrimaryVertices"),
    puSummary = cms.InputTag("addPileupInfo"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    PFMultiClusters = cms.InputTag('particleFlowClusterHGCalFromMultiCl'),

    ComputeIsoRings = cms.bool(False),
    barrelLowPt = cms.string('/home/llr/cms/ochando/TMVA/EID/weights/EIDmva_EB_1020_oldbarreltdrDR01_BDT.weights.xml'),
    barrelHighPt = cms.string('/home/llr/cms/ochando/TMVA/EID/weights/EIDmva_EB_20_oldbarreltdrDR01_BDT.weights.xml'),
    endcapLowPt = cms.string('/home/llr/cms/ochando/TMVA/EID/weights/HGCEIDmva_1020_trackepshowernoisolonghgcaltdrV3DR01preselmatch_BDT.weights.xml'),
    endcapHighPt = cms.string('/home/llr/cms/ochando/TMVA/EID/weights/HGCEIDmva_20_trackepshowernoisolonghgcaltdrV3DR01preselmatch_BDT.weights.xml'),
    cleanBarrel = cms.bool(True),
    dEdXWeights = dEdX
    )
