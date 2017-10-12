#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "EgammaTools/EgammaAnalysis/interface/ElectronIDHelper.h"
#include "EgammaTools/EgammaAnalysis/interface/LongDeps.h"

#include <iostream>
#include <iomanip>

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
        if (electron.isEB()) continue;
        eIDHelper_->computeHGCAL(electron,3.);
        std::cout << "sigmaUU " << eIDHelper_->sigmaUU() << std::endl;
        std::cout << "sigmaVV " << eIDHelper_->sigmaVV() << std::endl;
        std::cout << "sigmaEE " << eIDHelper_->sigmaEE() << std::endl;
        std::cout << "sigmaPP " << eIDHelper_->sigmaPP() << std::endl;

        LongDeps ld(eIDHelper_->energyPerLayer(3.,true));
        std::cout << "Nlayers " << ld.nLayers() << std::endl;

       std::cout << "GSF pt " << std::sqrt(electron.trackMomentumAtVtx().perp2()) << " " << electron.electronCluster()->energy() << std::endl;
    //   std::cout << electron.electronCluster()->size() << " " << electron.electronCluster()->hitsAndFractions().size() << std::endl;
    //   eIDHelper_->printHits(3.);

        std::cout << "First layer " << ld.firstLayer() << std::endl;
        std::cout << "Last layer " << ld.lastLayer() << std::endl;

        for (unsigned l=1;l<=52;++l) {
            std::cout << std::fixed << std::setw( 5 ) << std::setprecision( 2 ) << ld.energyPerLayer()[l] << " " ;
        }
        std::cout << std::endl;
        std::cout << " Energy EE " << ld.energyEE() << " EnergyFH " << ld.energyFH() << " EnergyBH " << ld.energyBH() <<std::endl;

        float measuredDepth, expectedDepth, expectedSigma;
        float depthCompatibility = eIDHelper_->clusterDepthCompatibility(ld,measuredDepth,expectedDepth, expectedSigma);
        std::cout << " Depth " << measuredDepth << " Exp. Depth " << expectedDepth << " ";
        std::cout << "Exp. Sigma " << expectedSigma <<  " Depth compatibility " <<depthCompatibility << std::endl;
    }

}

// define this as a plug-in
DEFINE_FWK_MODULE(ElectronIdTest);
