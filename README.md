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
Definitions and calls: 
```C++
ElectronIDHelper * eIDHelper_;
eIDHelper_->computeHGCAL(electron,3);

LongDeps ld(eIDHelper_->energyPerLayer(3.,true))

float measuredDepth, expectedDepth, expectedSigma;
float depthCompatibility = eIDHelper_->clusterDepthCompatibility(ld,measuredDepth,expectedDepth, expectedSigma);
```

| Variable | For ID | Description | Access method |
| ------------- | ------------- | ----- | ----- |
| | | **Cluster shapes** |
| `sigmaUU` | :white_check_mark: | Perpendicular cluster spread| `eIDHelper_->sigmaUU()` |
| `sigmaVV` | :white_check_mark: | Radial cluster spread | `eIDHelper_->sigmaVV()` |
| `sigmaEE` | :x: | Cluster spread in eta | `eIDHelper_->sigmaEE()` |
| `sigmaPP` | :x: | Cluster spread in phi | `eIDHelper_->sigmaPP()` |
| | | **Longitudinal / energy ** | `LongDeps ld(eIDHelper_->energyPerLayer(3.,true))`|
| `nLayers` | :white_check_mark: | Numer of layers in cluster | `ld.nLayers()` |
| `firstLayer` | :white_check_mark: | First layer of cluster | `ld.firstLayer()` |
| `lastLayer` | :x: | Last layer of cluster | `ld.lastLayer()` |
| `layEfrac10` | :white_check_mark: | First layer with 10% energy in EE | To be added, present in ntuple |
| `layEfrac90` | :white_check_mark: | First layer with 90% energy in EE | To be added, present in ntuple |
| `layerEnergy` | :x: | Energy per layer | `ld.energyPerLayer(layer)` |
| `energyEE` | :x: | Energy within cylinder in EE | `eIDHelper_->energyEE()` |
| `energyFH` | :x: | Energy within cylinder in EE | `eIDHelper_->energyFH()` |
| `energyBH` | :x: | Energy within cylinder in EE | `eIDHelper_->energyBH()` |
| `FHoverE` | :white_check_mark: | Energy within cylinder in EE | `energyFH/energyEE` |
| `HoverE` | :white_check_mark: | Energy within cylinder in EE | `(energyFH+energyBH)/energyEE` |
|  | | **Depth compatibility** |  ```float depthCompatibility = eIDHelper_->clusterDepthCompatibility(ld,measuredDepth,expectedDepth, expectedSigma);``` |
| `measuredDepth` | :white_check_mark: | Measured shower depth | See above |
| `expectedDepth` | :white_check_mark: | Expected shower depth | See above |
| `expectedSigma` | :white_check_mark: | Expected shower depth sigma | See above |
| `depthCompatibility` | :white_check_mark: | Depth compatibility | See above |
| | | **Track-based** | Also available from gsfEle directly |
| `ptAtEle` | :white_check_mark: | Track momentum (Pout)| `eIDHelper_->trackMomentumAtEleClus()` |
| `eOverPout` | :white_check_mark: | Electron cluster energy over Pout | `eIDHelper_->eEleClusterOverPout()` |
| | | **Cluster-track matching** |
| `deltaEta` | :white_check_mark: | dEta between Pout and cluster | `eIDHelper_->deltaEtaEleClusterTrackAtCalo()` |
| `deltaPhi` | :white_check_mark: | dPhi between Pout and cluster  | `eIDHelper_->deltaPhiEleClusterTrackAtCalo()` 

## Additional variables for gsfElectrons
KF track requires:
```C++
reco::TrackRef myTrackRef = ele.closestCtfTrackRef();
  validKF = (myTrackRef.isAvailable());
  validKF = (myTrackRef.isNonnull());  
```

| Variable | For ID | Description | Access method |
| ------------- | ------------- | ----- | ----- |
| `eta` | :white_check_mark: | Track eta | `electron.eta()` |
| `fbrem` | :white_check_mark: | (Pin-Pout)/Pin | `electron.fbrem()` |
| `gsfChi2` | :white_check_mark: | Chi^2 of GSF track | `ele.gsfTrack()->normalizedChi2()` |
| `kfChi2` | :white_check_mark: | Chi^2 KF track | `myTrackRef->normalizedChi2()` |
| `kfNhits` | :white_check_mark: | Number of hits for GSF track | `myTrackRef->hitPattern().trackerLayersWithMeasurement()` |
