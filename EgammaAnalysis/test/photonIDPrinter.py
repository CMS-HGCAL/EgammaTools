import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonID")

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')
process.load('EgammaTools.EgammaAnalysis.HGCalPhotonIDValueMap_cfi')

from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import dEdX_weights as dEdX

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_9_3_2/RelValSingleGammaPt25Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/321D865F-DBA6-E711-9859-0CC47A4D768C.root',
        '/store/relval/CMSSW_9_3_2/RelValSingleGammaPt25Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/84704C20-D7A6-E711-A677-0025905A608A.root',
        '/store/relval/CMSSW_9_3_2/RelValSingleGammaPt25Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/B012B757-D5A6-E711-B53F-0025905B85FC.root',
        '/store/relval/CMSSW_9_3_2/RelValSingleGammaPt25Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/B61D085E-DBA6-E711-9DC2-0CC47A78A418.root',
        '/store/relval/CMSSW_9_3_2/RelValSingleGammaPt25Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D2F3E811-D7A6-E711-8092-0CC47A7C3432.root'
    ),

#    eventsToProcess = cms.untracked.VEventRange('1:7498-1:7498'),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)


process.photonID = cms.EDAnalyzer('PhotonIdTest',
                                    EERecHits = cms.InputTag('HGCalRecHit:HGCEERecHits'),
                                    FHRecHits = cms.InputTag('HGCalRecHit:HGCHEFRecHits'),
                                    BHRecHits = cms.InputTag('HGCalRecHit:HGCHEBRecHits'),
                                    Photons = cms.InputTag('photonsFromMultiCl'),
                                    dEdXWeights = dEdX

)

process.output = cms.OutputModule("PoolOutputModule",
                                outputCommands = cms.untracked.vstring('drop *',
                                'keep *_photonsFromMultiCl_*_*',
                                'keep *_*_*_PhotonID'),
                                fileName = cms.untracked.string("output.root")
)

process.output_step = cms.EndPath(process.output)
#process.p = cms.Path(process.photonID * process.HGCalPhotonIDValueMap)
process.p = cms.Path(process.HGCalPhotonIDValueMap)
