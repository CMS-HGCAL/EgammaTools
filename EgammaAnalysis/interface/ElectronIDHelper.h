//--------------------------------------------------------------------------------------------------
//
// EGammaID Helper
//
// Helper Class to compute electron ID observables
//
// Authors: F. Beaudette,A. Lobanov
//--------------------------------------------------------------------------------------------------

#ifndef EGammaIDHelper_H
#define EGammaIDHelper_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"

#include <vector>

class EgammaIDHelper {
public:
  EgammaIDHelper();
  ~EgammaIDHelper(){;}


private:
  bool initialized_;
};

#endif
