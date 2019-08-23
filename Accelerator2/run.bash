#!/bin/bash

# Geant4 Accelerator Beam Optics (GABO)

make clean; make -j2;

outputRootFile="/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1_accelerator1_rp0_accelerator2.root"

./accelerator $outputRootFile 2

