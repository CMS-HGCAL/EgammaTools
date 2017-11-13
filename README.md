# EgammaTools
Helper functions for electron/photon ID variables in the HGCAL. Compatible with gsfElectrons and CaloClusters.

## Usage

Setup:
```Bash
cmsrel CMSSW_9_3_2
cd CMSSW_9_3_2
cd src/
cmsenv
git clone git@github.com:CMS-HGCAL/EgammaTools.git
```

* See the test/ElectronIDTest.cc to see how to setup the Helper class and use it to get the information.

* Can be used from within the [CMS-HGCAL/reco-ntuples](https://github.com/CMS-HGCAL/reco-ntuples) using the `topic_eleID_helper` branch.


## Available variables
See list of variables here: https://github.com/CMS-HGCAL/EgammaTools/blob/master/VARIABLES.md

## Electron ID (BDT)
See instructions here: https://github.com/CMS-HGCAL/EgammaTools/blob/master/ELECTRONBDT.md
