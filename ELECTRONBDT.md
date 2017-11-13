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

## Barrel/Endcap
To distinguish between a barrel and a endcap electron, it is recommended to use the **.isEB()**  of the GsfElectrons rather than an eta cut.

## Endcap Preselection
Additional cuts to clean bad electron clusters based on variables in the value maps
```
sigmaUU > 0
fbrem > -1
measuredDepth < 40
nLayers > 20
```
  
## Recommended cuts
   * Barrel

   * Endcaps
For Pt>20 GeV BDT> 0.67 (95% efficiency)
For 10<Pt<20 GeV BDT > 0.73 (80% efficiency)

