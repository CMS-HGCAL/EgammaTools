//--------------------------------------------------------------------------------------------------
//
// ElectronBDT Helper
//
// Helper Class to compute electron ID observables
//
// Authors: F. Beaudette,A. Lobanov, C. Ochando
//--------------------------------------------------------------------------------------------------

#ifndef ElectronBDTHelper_H
#define ElectronBDTHelper_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "EgammaTools/EgammaAnalysis/interface/ElectronIDHelper.h"

#include "TMVA/Reader.h"

class ElectronBDTHelper {
public:
    ElectronBDTHelper(){}
    ElectronBDTHelper(const edm::ParameterSet &, edm::ConsumesCollector && iC);
    ~ElectronBDTHelper();
    float computeBDT(const reco::GsfElectron & electron);
    void eventInit(const edm::Event& iEvent,const edm::EventSetup &iSetup) ;
    inline void setElectonIDHelper( ElectronIDHelper * helper) { eIDHelper_ = helper;}

private:
    float puDensity(float z, int npu, float z0,float sigmaz) const;
    void initReader(TMVA::Reader& reader, const std::string& file, bool barrel);

    // ----------member data ---------------------------
    edm::EDGetTokenT<std::vector<reco::Vertex>> verticesToken_;
    edm::EDGetTokenT<std::vector<PileupSummaryInfo>> puSummaryInfoToken_;
    edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;

    ElectronIDHelper * eIDHelper_;

    float radius_;
    edm::FileInPath barrelLowPtFile_;
    edm::FileInPath barrelHighPtFile_;
    edm::FileInPath endcapLowPtFile_;
    edm::FileInPath endcapHighPtFile_;

    float pTLimit_;

    std::unique_ptr<TMVA::Reader> barrelLowPtReader_;
    std::unique_ptr<TMVA::Reader> barrelHighPtReader_;
    std::unique_ptr<TMVA::Reader> endcapLowPtReader_;
    std::unique_ptr<TMVA::Reader> endcapHighPtReader_;

    // Variables

    float tmva_ele_kfhits;
    float tmva_ele_gsfhits;
    float tmva_ele_kfchi2;
    float tmva_ele_gsfchi2;
    float tmva_ele_fbrem;

    // E-p matching
    float tmva_ele_eelepout;
    float tmva_ele_deltaetaele;
    float tmva_ele_deltaphiele;

    // HGC-specific
    float tmva_ele_sigmauu;
    float tmva_ele_sigmavv;
    float tmva_ele_hgc_eigenvalues1;
    float tmva_ele_hgc_eigenvalues2;
    float tmva_ele_hgc_eigenvalues3;
    float tmva_ele_hgc_sigmas1;
    float tmva_ele_hgc_sigmas2;
    float tmva_ele_hgc_sigmas3;
    float tmva_ele_hgc_pcaAxisX;
    float tmva_ele_hgc_pcaAxisY;
    float tmva_ele_hgc_pcaAxisZ;
    float tmva_ele_hgc_pcaPosX;
    float tmva_ele_hgc_pcaPosY;
    float tmva_ele_hgc_pcaPosZ;
    float tmva_ele_hgc_FHoverEE;
    float tmva_ele_hgc_nlay;
    float tmva_ele_hgc_firstlay;
    float tmva_ele_hgc_lastlay;
    float tmva_ele_hgc_EE4overEE;
    float tmva_ele_hgc_layEfrac10;
    float tmva_ele_hgc_layEfrac90;
    float tmva_ele_hgc_depthCompat;

    float tmva_ele_oldsigmaietaieta;
    float tmva_ele_oldsigmaiphiiphi;
    float tmva_ele_oldcircularity;
    float tmva_ele_oldr9;
    float tmva_ele_scletawidth;
    float tmva_ele_sclphiwidth;
    float tmva_ele_he;
    float tmva_ele_ep;
    float tmva_ele_eseedpout;
    float tmva_ele_deltaetaseed;
    float tmva_ele_deltaphiseed;

    // Spectator Variables
    float tmva_ele_pT;
    float tmva_ele_eta;
    float tmva_scl_eta;
    float tmva_ele_ET;
    float tmva_Nvtx;
    float tmva_NPU;
    float tmva_PUdensity;

};

#endif
