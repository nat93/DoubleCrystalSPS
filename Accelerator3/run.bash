#!/bin/bash

# Geant4 Accelerator Beam Optics (GABO)

make clean; make -j2;

outputRootFile="/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1_accelerator1_rp0_accelerator2_crystal2_accelerator3.root"          # without target
#outputRootFile="/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1_accelerator1_rp0_accelerator2_target_crystal2_accelerator3.root"  # with target

./accelerator $outputRootFile 2

