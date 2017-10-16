import FWCore.ParameterSet.Config as cms

process = cms.Process("PhotonID")

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryExtended2023D17Reco_cff')
from RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi import dEdX_weights as dEdX

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        '/store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/D0226E59-00A7-E711-AA65-0CC47A78A426.root',
        '/store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/FE5CADD8-01A7-E711-B465-0CC47A7C35A4.root',
        '/store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/E8E9A7E8-02A7-E711-A8FA-0CC47A4C8E46.root',
        '/store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/9E833A7E-08A7-E711-A414-0025905B859E.root',
        '/store/relval/CMSSW_9_3_2/RelValSingleElectronPt15Eta1p7_2p7/GEN-SIM-RECO/93X_upgrade2023_realistic_v2_2023D17noPU-v1/10000/E4C8A780-08A7-E711-AEF4-0025905A6090.root'
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

process.p = cms.Path(process.photonID)
