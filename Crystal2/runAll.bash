#!/bin/bash

## without RP0
#inputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_null_accelerator2.root"
#outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_null_accelerator2_crystal2_"		#with crystal
#outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_null_accelerator2_crystal2_null_"	#without crystal

## with RP0 plate of W
#inputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_simple_accelerator2.root"
#outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_simple_accelerator2_crystal2_"	#with crystal
#outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_simple_accelerator2_crystal2_null_"	#without crystal

## with RP0 layers structure
inputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers_accelerator2.root"
#outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers_accelerator2_crystal2_"	#with crystal
outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_accelerator1_rp0_layers_accelerator2_crystal2_null_"	#without crystal

#outputRootFile="/media/andrii/F492773C92770302/DoubleCrystalSPS_DATA/output_crystal1_accelerator1_rp0_accelerator2_target_crystal2_";  # with target

nEntries=0;

#./channeling run.mac $inputRootFile $outputRootFile$nEntries.root $nEntries


for iFile in $(seq 0 19)
do
	echo "file index = $iFile"

	((nEntries = iFile * 10000));

	echo "#!/bin/bash" > runTmp.sh
	echo "source /home/gred/root_34_36/bin/thisroot.sh;" >> runTmp.sh
	echo "source /home/gred/geant4.10.02.p02/geant4.10.02.p02-build/geant4make.sh;" >> runTmp.sh
	echo "./channeling run.mac $inputRootFile $outputRootFile$iFile.root $nEntries" >> runTmp.sh

	chmod a+x runTmp.sh
	screen -S natochii_thr$iFile -L -d -m "./runTmp.sh"

	echo "wait for 1 sec ..."
	sleep 1;
done

screen -ls
