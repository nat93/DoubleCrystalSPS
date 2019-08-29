#!/bin/bash

# Geant4 Accelerator Beam Optics (GABO)

make clean; make -j2;

## without RP0
#inputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_null.root"
#outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_null_accelerator2.root"

## with RP0 plate of W
#inputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_simple.root"
#outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_simple_accelerator2.root"

## with RP0 layers structure
inputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers.root"
outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers_accelerator2.root"

./accelerator $inputRootFile $outputRootFile 2

