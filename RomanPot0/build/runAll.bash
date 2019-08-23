#!/bin/bash

inputRootFile="/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1_accelerator1.root"
outputRootFile="/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1_accelerator1_rp0.root";

./romanpot0 run.mac $inputRootFile $outputRootFile
