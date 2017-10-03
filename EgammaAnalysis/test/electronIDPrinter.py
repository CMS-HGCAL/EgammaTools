import FWCore.ParameterSet.Config as cms

process = cms.Process("ElectronID")

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')
from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import dEdX_weights as dEdX

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_9_3_0_pre4/RelValTTbar_14TeV/GEN-SIM-RECO/PU25ns_93X_upgrade2023_realistic_v0_D17PU200-v1/00000/082041D3-1E89-E711-80AA-0242AC130002.root'
    ),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)


process.electronID = cms.EDAnalyzer('ElectronIdTest',
                                    EERecHits = cms.InputTag('HGCalRecHit:HGCEERecHits'),
                                    GsfElectrons = cms.InputTag('ecalDrivenGsfElectronsFromMultiCl'),
                                    dEdXWeights = dEdX

)

process.p = cms.Path(process.electronID)
