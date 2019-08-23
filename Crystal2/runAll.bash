#!/bin/bash

inputRootFile="/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1_accelerator1_rp0_accelerator2.root";
outputRootFile="/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1_accelerator1_rp0_accelerator2_crystal2_";          # without target
#outputRootFile="/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1_accelerator1_rp0_accelerator2_target_crystal2_";  # with target

nEntries=0;
#nEntries=100000;
#nEntries=200000;
#nEntries=300000;
#nEntries=400000;
#nEntries=500000;

./channeling run.mac $inputRootFile $outputRootFile$nEntries.root $nEntries
