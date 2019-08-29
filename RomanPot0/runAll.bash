#!/bin/bash

inputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1.root"

## without RP0
outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_null.root"

## with RP0 plate of W
#outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_simple.root"

## with RP0 layers structure
#outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers.root"

./romanpot0 run.mac $inputRootFile $outputRootFile
