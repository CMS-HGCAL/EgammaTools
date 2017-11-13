import FWCore.ParameterSet.Config as cms

process = cms.Process("ElectronID")

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')
process.load('EgammaTools.EgammaAnalysis.HGCalElectronIDValueMap_cfi')

from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import dEdX_weights as dEdX

process.load('EgammaTools.EgammaAnalysis.HGCalElectronFilter_cfi')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
'root://cms-xrd-global.cern.ch//store/mc/PhaseIITDRFall17DR/DYToLL-M-50_0J_14TeV-madgraphMLM-pythia8/GEN-SIM-RECO/PU200_93X_upgrade2023_realistic_v2-v1/00000/BE500A88-5EAD-E711-8E07-0242AC110012.root',
'root://cms-xrd-global.cern.ch//store/mc/PhaseIITDRFall17DR/DYToLL-M-50_0J_14TeV-madgraphMLM-pythia8/GEN-SIM-RECO/PU200_93X_upgrade2023_realistic_v2-v1/00000/78E43CDF-5EAD-E711-BA4A-0242AC110002.root',
'root://cms-xrd-global.cern.ch//store/mc/PhaseIITDRFall17DR/DYToLL-M-50_0J_14TeV-madgraphMLM-pythia8/GEN-SIM-RECO/PU200_93X_upgrade2023_realistic_v2-v1/00000/04CC740B-5FAD-E711-9A4A-0242AC110008.root',
'root://cms-xrd-global.cern.ch//store/mc/PhaseIITDRFall17DR/DYToLL-M-50_0J_14TeV-madgraphMLM-pythia8/GEN-SIM-RECO/PU200_93X_upgrade2023_realistic_v2-v1/00000/A8640BD9-5EAD-E711-9B9C-0242AC11000D.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/7889725A-F1A6-E711-8442-0CC47A4D7618.root'
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/56F81F93-F5A6-E711-A87D-0CC47A4C8E14.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/0A26CCF0-F5A6-E711-8C50-0025905B857E.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/56D9E02B-F7A6-E711-8A07-0CC47A4C8E8A.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/78B617CB-F4A6-E711-BA4C-0CC47A4D7690.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/9402F52F-F5A6-E711-99B9-0CC47A7C356A.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/3C7CDE63-F7A6-E711-A13F-0CC47A4D7618.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/9A702D5A-F6A6-E711-BB94-0025905A6060.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/00FF6760-F8A6-E711-AA68-0025905A60D6.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/EA4B5A19-F8A6-E711-86AD-0025905A60B4.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/1AF12BCC-F8A6-E711-B089-0025905A60D0.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/2AF566EE-FAA6-E711-BA3D-0025905B860E.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/C06FD61F-FEA6-E711-AFD2-0025905B856C.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/5E776718-06A7-E711-9EF1-0CC47A7C34E6.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/52B58CEB-08A7-E711-B5A3-0CC47A78A4A6.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/321C4442-09A7-E711-9BBD-0CC47A4C8F0A.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/4E5D5E53-08A7-E711-8FFC-003048FF9ABC.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/C00FC03B-12A7-E711-A207-0CC47A4C8ECE.root',
#'root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_3_2/RelValQCD_Pt-15To7000_Flat_14TeV/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/DE1D2C3F-12A7-E711-8C9C-0025905A608E.root'
    ),

#    eventsToProcess = cms.untracked.VEventRange('1:7498-1:7498'),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
)



process.electronID = cms.EDAnalyzer('ElectronIdTest',
                                    EERecHits = cms.InputTag('HGCalRecHit:HGCEERecHits'),
                                    FHRecHits = cms.InputTag('HGCalRecHit:HGCHEFRecHits'),
                                    BHRecHits = cms.InputTag('HGCalRecHit:HGCHEBRecHits'),
                                    GsfElectrons = cms.InputTag('cleanedEcalDrivenGsfElectronsFromMultiCl'),
                                    PFMultiClusters = cms.InputTag('particleFlowClusterHGCalFromMultiCl'),
                                    dEdXWeights = dEdX,
                                    pcaRadius = cms.double(3.),
                                    vertices = cms.InputTag("offlinePrimaryVertices"),
                                    puSummary = cms.InputTag("addPileupInfo"),
                                    beamSpot = cms.InputTag("offlineBeamSpot"),
                                    barrelLowPt = cms.FileInPath('EgammaTools/EgammaAnalysis/data/EIDmva_EB_1020_oldbarreltdrDR01_BDT.weights.xml'),
                                    barrelHighPt = cms.FileInPath('EgammaTools/EgammaAnalysis/data/EIDmva_EB_20_oldbarreltdrDR01_BDT.weights.xml'),
                                    endcapLowPt = cms.FileInPath('EgammaTools/EgammaAnalysis/data/HGCEIDmva_1020_trackepshowernoisolonghgcaltdrV3DR01preselmatch_BDT.weights.xml'),
                                    endcapHighPt = cms.FileInPath('EgammaTools/EgammaAnalysis/data/HGCEIDmva_20_trackepshowernoisolonghgcaltdrV3DR01preselmatch_BDT.weights.xml'),
)
process.HGCalElectronIDValueMap.GsfElectrons = cms.InputTag('cleanedEcalDrivenGsfElectronsFromMultiCl')
process.HGCalElectronIDValueMap.PFMultiClusters = cms.InputTag('particleFlowClusterHGCalFromMultiCl')


process.output = cms.OutputModule("PoolOutputModule",
                                outputCommands = cms.untracked.vstring('drop *',
                                'keep *_ecalDrivenGsfElectronsFromMultiCl_*_*',
                                'keep *_cleanedEcalDrivenGsfElectronsFromMultiCl_*_*',
                                'keep *_*_*_ElectronID'),
                                fileName = cms.untracked.string("output.root")
)

process.output_step = cms.EndPath(process.output)
process.p = cms.Path(process.cleanedEcalDrivenGsfElectronsFromMultiCl * process.electronID * process.HGCalElectronIDValueMap)
#process.p = cms.Path(process.cleanedEcalDrivenGsfElectronsFromMultiCl)
