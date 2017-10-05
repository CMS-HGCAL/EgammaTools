import FWCore.ParameterSet.Config as cms

process = cms.Process("ElectronID")

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')
from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import dEdX_weights as dEdX

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(5) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        '/store/relval/CMSSW_9_3_0_pre4/RelValTTbar_14TeV/GEN-SIM-RECO/PU25ns_93X_upgrade2023_realistic_v0_D17PU200-v1/00000/082041D3-1E89-E711-80AA-0242AC130002.root'
    'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/2E2C7104-E1A6-E711-817B-0CC47A7C3612.root',
    'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/6AB8C4AA-E2A6-E711-89D9-0025905B856C.root',
    'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/78BD7B0D-E3A6-E711-B085-0CC47A4D7690.root',
    'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/8E77B685-E7A6-E711-B95C-0CC47A4D7618.root',
    'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/9CA35A6F-D9A6-E711-A094-0CC47A7C347E.root',
    'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/A02B4256-E3A6-E711-9868-0CC47A4D7658.root',
    'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0EBAD5B-E1A6-E711-9C6B-0CC47A7C347E.root',
    'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/E61313BB-EDA6-E711-AAF4-003048FFD772.root',
    'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/F0A4829C-E3A6-E711-BBC1-0025905A60A8.root'

    #'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-DIGI-RAW/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/401F1F71-DFA6-E711-A195-0025905A612E.root',
    #'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-DIGI-RAW/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/5279CD99-DDA6-E711-A473-0CC47A7C360E.root',
    #'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-DIGI-RAW/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/82AF4D97-E0A6-E711-9F02-0025905A48D0.root',
    #'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-DIGI-RAW/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/8EEFAD04-E5A6-E711-9C96-0CC47A78A4B8.root',
    #'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-DIGI-RAW/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/DC98E8BD-D6A6-E711-ACCC-0025905B85FC.root'
    ),


    duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)


process.electronID = cms.EDAnalyzer('ElectronIdTest',
                                    EERecHits = cms.InputTag('HGCalRecHit:HGCEERecHits'),
                                    FHRecHits = cms.InputTag('HGCalRecHit:HGCHEFRecHits'),
                                    BHRecHits = cms.InputTag('HGCalRecHit:HGCHEBRecHits'),
                                    GsfElectrons = cms.InputTag('ecalDrivenGsfElectronsFromMultiCl'),
                                    dEdXWeights = dEdX

)

process.p = cms.Path(process.electronID)
