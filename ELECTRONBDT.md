# Electron BDT

## Installing the necessary code

Setup:
```Bash
cmsrel CMSSW_9_3_2
cd CMSSW_9_3_2
cd src/
cmsenv
git clone -b bdthelper git@github.com:beaudett/EgammaTools.git
```
## Usage
   * It was observed that the reconstruction often reconstructs multiple electrons, and a cleaning should be applied before computing the multivariate quality estimator. It is done by the HGCalElectronFilter. The corresponding cfi is in =python/HGCalElectronFilter_cfi.py= which has to be run first. It produces a collection called **cleanedEcalDrivenGsfElectronsFromMultiCl**. Any subsquent module looking for electrons should use the collection thus produced.
  




## Recommended cuts
