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
Additional cuts to clean bad HGCAL electron clusters based on variables in the value maps
```
ecEnergy > 0
sigmaUU > 0
fbrem > -1
measuredDepth < 40
nLayers > 20
```
  
## Recommended ID cuts

### Endcap (HGCAL)
#### `pT > 20` GeV
Name | Bkg Eff | Sig Eff | BDT score
-----|---------|---------|----------
Tight | 0.1    | 76      | 0.983
Medium | 1     | 96      | 0.591
Loose | 10     | 100     | -0.919

#### `10 < pT < 20` GeV
Name | Bkg Eff | Sig Eff | BDT score
-----|---------|---------|----------
Tight | 0.1    | 43      | 0.969
Medium | 1     | 78      | 0.777
Loose | 10     | 95      | -0.320

### Barrel (isEB == 1)
#### `pT > 20` GeV
Name | Bkg Eff | Sig Eff | BDT score
-----|---------|---------|----------
Tight | 0.1 | 60 | 0.988
Medium | 1 | 92 | 0.723
Loose | 10 | 99 | -0.797

#### `10 < pT < 20` GeV
Name | Bkg Eff | Sig Eff | BDT score
-----|---------|---------|----------
Tight | 0.1    | 30      | 0.986
Medium| 1     | 81      |0.855
Loose | 10     | 98     | -0.661


### Previous values (same training)

#### Barrel
pT range | 95% Efficiency | 80% efficiency
-------- |---------|-----
`10-20` GeV | `BDT > 0.203` | `BDT > 0.869`
`> 20` GeV | `BDT > 0.452` | –

#### Endcap (HGCAL)
pT range | 95% Efficiency | 80% efficiency
-------- |---------|-----
`10-20` GeV | `BDT > -0.33` | `BDT > 0.73`
`> 20` GeV | `BDT> 0.67` | –



