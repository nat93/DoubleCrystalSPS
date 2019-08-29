#!/bin/bash

# Geant4 Accelerator Beam Optics (GABO)

make clean; make -j2;

outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1.root"

./accelerator $outputRootFile 2

