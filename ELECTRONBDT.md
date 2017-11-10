# Electron BDT

## Installing the necessary code

Setup:
```Bash
cmsrel CMSSW_9_3_2
cd CMSSW_9_3_2
cd src/
cmsenv
git clone git@github.com:CMS-HGCAL/EgammaTools.git
```
## Usage
   * It was observed that the reconstruction often reconstructs multiple electrons, and a cleaning should be applied before computing the multivariate quality estimator. It is done by the `HGCalElectronFilter`. The corresponding cfi is in `python/HGCalElectronFilter_cfi.py` which has to be run first. It produces a collection called **cleanedEcalDrivenGsfElectronsFromMultiCl**. Any subsquent module looking for electrons should use the collection thus produced.
   * Once the collection is cleaned, the *ValueMapProducer* can be run thanks to the `python/HGCalElectronIDValueMap_cfi.py` configuration fragment. **Make sure that the "electrons" parameter that specifies the input collection is set to cleanedEcalDrivenGsfElectronsFromMultiCl**
   
## Preselection
Additional cuts to clean bad electron clusters based on variables in the value maps
```
ele.ele_siguu() > 0
ele.fbrem() > -1
ele.ele_realDepth() < 50
ele.ele_nlay() > 20
```
  
## Recommended cuts
For Pt>20 GeV BDT> 0.67 (95% efficiency)
For 10<Pt<20 GeV BDT > 0.73 (80% efficiency)

