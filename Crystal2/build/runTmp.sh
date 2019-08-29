#!/bin/bash
source /home/gred/root_34_36/bin/thisroot.sh;
source /home/gred/geant4.10.02.p02/geant4.10.02.p02-build/geant4make.sh;
./channeling run.mac ~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers_accelerator2.root ~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers_accelerator2_crystal2_null_19.root 190000
