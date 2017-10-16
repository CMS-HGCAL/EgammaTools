import FWCore.ParameterSet.Config as cms

process = cms.Process("ElectronID")

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')
process.load('EgammaTools.EgammaAnalysis.HGCalElectronIDValueMap_cfi')

from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import dEdX_weights as dEdX

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
#        '/store/relval/CMSSW_9_3_0_pre4/RelValTTbar_14TeV/GEN-SIM-RECO/PU25ns_93X_upgrade2023_realistic_v0_D17PU200-v1/00000/082041D3-1E89-E711-80AA-0242AC130002.root'
    #'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/2E2C7104-E1A6-E711-817B-0CC47A7C3612.root',
    #   'root://polgrid4.in2p3.fr//store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/6AB8C4AA-E2A6-E711-89D9-0025905B856C.root','
    #   'root://polgrid4.in2p3.fr//store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/78BD7B0D-E3A6-E711-B085-0CC47A4D7690.root','
    #   'root://polgrid4.in2p3.fr//store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/8E77B685-E7A6-E711-B95C-0CC47A4D7618.root','
    #   'root://polgrid4.in2p3.fr//store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/9CA35A6F-D9A6-E711-A094-0CC47A7C347E.root','
    #   'root://polgrid4.in2p3.fr//store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/A02B4256-E3A6-E711-9868-0CC47A4D7658.root','
    #   'root://polgrid4.in2p3.fr//store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0EBAD5B-E1A6-E711-9C6B-0CC47A7C347E.root','
    #   'root://polgrid4.in2p3.fr//store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/E61313BB-EDA6-E711-AAF4-003048FFD772.root','
    #   'root://polgrid4.in2p3.fr//store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValZEE_14/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/F0A4829C-E3A6-E711-BBC1-0025905A60A8.root''

#    'root://polgrid4.in2p3.fr//store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root'

'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/7889725A-F1A6-E711-8442-0CC47A4D7618.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/56F81F93-F5A6-E711-A87D-0CC47A4C8E14.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/0A26CCF0-F5A6-E711-8C50-0025905B857E.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/56D9E02B-F7A6-E711-8A07-0CC47A4C8E8A.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/78B617CB-F4A6-E711-BA4C-0CC47A4D7690.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/9402F52F-F5A6-E711-99B9-0CC47A7C356A.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/3C7CDE63-F7A6-E711-A13F-0CC47A4D7618.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/9A702D5A-F6A6-E711-BB94-0025905A6060.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/00FF6760-F8A6-E711-AA68-0025905A60D6.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/EA4B5A19-F8A6-E711-86AD-0025905A60B4.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/1AF12BCC-F8A6-E711-B089-0025905A60D0.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/2AF566EE-FAA6-E711-BA3D-0025905B860E.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/C06FD61F-FEA6-E711-AFD2-0025905B856C.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/5E776718-06A7-E711-9EF1-0CC47A7C34E6.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/52B58CEB-08A7-E711-B5A3-0CC47A78A4A6.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/321C4442-09A7-E711-9BBD-0CC47A4C8F0A.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/4E5D5E53-08A7-E711-8FFC-003048FF9ABC.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/C00FC03B-12A7-E711-A207-0CC47A4C8ECE.root',
'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/DE1D2C3F-12A7-E711-8C9C-0025905A608E.root'
    ),

#    eventsToProcess = cms.untracked.VEventRange('1:7498-1:7498'),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)


process.electronID = cms.EDAnalyzer('ElectronIdTest',
                                    EERecHits = cms.InputTag('HGCalRecHit:HGCEERecHits'),
                                    FHRecHits = cms.InputTag('HGCalRecHit:HGCHEFRecHits'),
                                    BHRecHits = cms.InputTag('HGCalRecHit:HGCHEBRecHits'),
                                    GsfElectrons = cms.InputTag('ecalDrivenGsfElectronsFromMultiCl'),
                                    dEdXWeights = dEdX

)

process.output = cms.OutputModule("PoolOutputModule",
                                outputCommands = cms.untracked.vstring('keep *'),
                                fileName = cms.untracked.string("output.root")
)

process.output_step = cms.EndPath(process.output)
process.p = cms.Path(process.electronID * process.HGCalElectronIDValueMap)
