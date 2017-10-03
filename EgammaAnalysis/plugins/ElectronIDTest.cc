#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "EgammaTools/EgammaAnalysis/interface/ElectronIDHelper.h"

#include <iostream>

class ElectronIdTest : public edm::one::EDAnalyzer<edm::one::WatchRuns, edm::one::SharedResources> {

public:

    ElectronIdTest();
    explicit ElectronIdTest(const edm::ParameterSet &);
    ~ElectronIdTest();

    virtual void beginRun(edm::Run const &iEvent, edm::EventSetup const &) override;
    virtual void endRun(edm::Run const &iEvent, edm::EventSetup const &) override;

private:
     virtual void analyze(const edm::Event &, const edm::EventSetup &) override;

private:
     ElectronIDHelper * eIDHelper_;
     edm::InputTag gsfElectronTag_;
     edm::EDGetTokenT<std::vector<reco::GsfElectron>> electrons_;
};

ElectronIdTest::ElectronIdTest(){;}

ElectronIdTest::~ElectronIdTest(){;}

ElectronIdTest::ElectronIdTest(const edm::ParameterSet &iConfig)
{
    eIDHelper_ = new ElectronIDHelper(iConfig ,consumesCollector());
    gsfElectronTag_ = iConfig.getParameter<edm::InputTag>("GsfElectrons");
    electrons_ = consumes<std::vector<reco::GsfElectron>>(gsfElectronTag_);
}

void ElectronIdTest::beginRun(edm::Run const &iEvent, edm::EventSetup const &) {;}

void ElectronIdTest::endRun(edm::Run const &iEvent, edm::EventSetup const &) {;}

void ElectronIdTest::analyze(const edm::Event &iEvent, const edm::EventSetup &iSetup) {
    eIDHelper_->eventInit(iEvent,iSetup);

    edm::Handle<std::vector<reco::GsfElectron>> eleHandle;
    iEvent.getByToken(electrons_, eleHandle);
    for (auto electron : *eleHandle) {
        std::cout << " Electron eta pt" << electron.eta() << " " << electron.pt() << std::endl;
//        std::cout << " Cluster " << electron.electronCluster()->energy() << std::endl;
        eIDHelper_->computeHGCAL(electron,3.);
    }

}

// define this as a plug-in
DEFINE_FWK_MODULE(ElectronIdTest);
