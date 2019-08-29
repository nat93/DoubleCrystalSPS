#!/bin/bash

inputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1.root"
outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers.root";

./romanpot0 run.mac $inputRootFile $outputRootFile
