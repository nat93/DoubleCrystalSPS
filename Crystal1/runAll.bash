#!/bin/bash

outputRootFile="~/home2/DoubleCrystalSPSsimData/output_crystal1_";

for iFile in $(seq 0 19)
do
	echo "file index = $iFile"

	echo "#!/bin/bash" > runTmp.sh
	echo "source /home/gred/root_34_36/bin/thisroot.sh;" >> runTmp.sh
	echo "source /home/gred/geant4.10.02.p02/geant4.10.02.p02-build/geant4make.sh;" >> runTmp.sh
	echo "./channeling run.mac $outputRootFile$iFile.root" >> runTmp.sh

	chmod a+x runTmp.sh
	screen -S natochii_thr$iFile -L -d -m "./runTmp.sh"

	echo "wait for 1 sec ..."
	sleep 1;
done

screen -ls
