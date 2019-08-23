TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "/home/andrii/root/include"
INCLUDEPATH += "/home/andrii/GEANT4.10.2/geant4.10.02.p02-install/include/Geant4"
INCLUDEPATH += "/home/andrii/GEANT4.10.2/CLHEP-install/include"
INCLUDEPATH += "/home/andrii/pythia/pythia8185/include"
INCLUDEPATH += "include"

LIBS += -L/home/andrii/root/lib -lGui -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread
LIBS += -L/home/andrii/GEANT4.10.2/geant4.10.02.p02-build/outputs/library/Linux-g++ -lG4analysis -lG4digits_hits -lG4error_propagation -lG4event -lG4Tree -lG4FR -lG4GMocren -lG4visHepRep -lG4RayTracer -lG4VRML -lG4vis_management -lG4modeling -lG4interfaces -lG4persistency -lG4readout -lG4physicslists -lG4run -lG4tracking -lG4parmodels -lG4processes  -lG4track -lG4particles -lG4geometry -lG4materials -lG4graphics_reps -lG4intercoms -lG4global
LIBS += -L/home/andrii/GEANT4.10.2/CLHEP-install/lib -lCLHEP -lCLHEP-2.1.3.0 -lCLHEP-Cast-2.1.3.0 -lCLHEP-Evaluator-2.1.3.0 -lCLHEP-Exceptions-2.1.3.0

SOURCES += \
    channeling.cc \
    src/ExExChAntiBarionBuilder.cc \
    src/ExExChDetectorConstruction.cc \
    src/ExExChDetectorConstructionMessenger.cc \
    src/ExExChEventAction.cc \
    src/ExExChHadronElasticPhysics.cc \
    src/ExExChHadronPhysicsQGSP_BIC.cc \
    src/ExExChHyperonFTFPBuilder.cc \
    src/ExExChIonPhysics.cc \
    src/ExExChParticleUserInfo.cc \
    src/ExExChPhysicsList.cc \
    src/ExExChPhysicsListMessenger.cc \
    src/ExExChPhysListEmStandardSS.cc \
    src/ExExChPiKBuilder.cc \
    src/ExExChPrimaryGeneratorAction.cc \
    src/ExExChProcessChanneling.cc \
    src/ExExChProtonBuilder.cc \
    src/ExExChRunAction.cc \
    src/ExExChSensitiveDetector.cc \
    src/ExExChSensitiveDetectorHit.cc \
    src/ExExChStackingAction.cc \
    src/ExExChStackingActionMessenger.cc \
    src/ExExChTrackingAction.cc \
    src/ExExChUserActionInitialization.cc \
    src/XCrystalCharacteristicArray.cc \
    src/XCrystalIntegratedDensityHub.cc \
    src/XCrystalIntegratedDensityPlanar.cc \
    src/XCrystalPlanarMoliereElectricField.cc \
    src/XCrystalPlanarMoliereElectronDensity.cc \
    src/XCrystalPlanarMolierePotential.cc \
    src/XCrystalPlanarMoliereTempPotential.cc \
    src/XCrystalPlanarNucleiDensity.cc \
    src/XLatticeManager3.cc \
    src/XLogicalAtomicLattice.cc \
    src/XLogicalAtomicLatticeDiamond.cc \
    src/XLogicalAtomicLatticeDiamondSingleAtom.cc \
    src/XLogicalBase.cc \
    src/XLogicalLattice.cc \
    src/XPhysicalLattice.cc \
    src/XUnitCell.cc \
    src/XVCrystalCharacteristic.cc \
    src/XVCrystalIntegratedDensity.cc \
    src/XVCrystalPlanarAnalytical.cc \
    src/XWrapperContinousDiscreteProcess.cc \
    src/XWrapperDiscreteProcess.cc \
    src/ExExChSteppingAction.cc

DISTFILES += \
    mac/vis.mac \
    mac/run.mac \
    runAll.bash

HEADERS += \
    include/ExExChAnalysis.hh \
    include/ExExChAntiBarionBuilder.hh \
    include/ExExChDetectorConstruction.hh \
    include/ExExChDetectorConstructionMessenger.hh \
    include/ExExChEventAction.hh \
    include/ExExChHadronElasticPhysics.hh \
    include/ExExChHadronPhysicsQGSP_BIC.hh \
    include/ExExChHyperonFTFPBuilder.hh \
    include/ExExChIonPhysics.hh \
    include/ExExChParticleUserInfo.hh \
    include/ExExChPhysicsList.hh \
    include/ExExChPhysicsListMessenger.hh \
    include/ExExChPhysListEmStandardSS.hh \
    include/ExExChPiKBuilder.hh \
    include/ExExChPrimaryGeneratorAction.hh \
    include/ExExChProcessChanneling.hh \
    include/ExExChProtonBuilder.hh \
    include/ExExChRunAction.hh \
    include/ExExChSensitiveDetector.hh \
    include/ExExChSensitiveDetectorHit.hh \
    include/ExExChStackingAction.hh \
    include/ExExChStackingActionMessenger.hh \
    include/ExExChTrackingAction.hh \
    include/ExExChUserActionInitialization.hh \
    include/XCrystalCharacteristicArray.hh \
    include/XCrystalIntegratedDensityHub.hh \
    include/XCrystalIntegratedDensityPlanar.hh \
    include/XCrystalPlanarMoliereElectricField.hh \
    include/XCrystalPlanarMoliereElectronDensity.hh \
    include/XCrystalPlanarMolierePotential.hh \
    include/XCrystalPlanarMoliereTempPotential.hh \
    include/XCrystalPlanarNucleiDensity.hh \
    include/XLatticeManager3.hh \
    include/XLogicalAtomicLattice.hh \
    include/XLogicalAtomicLatticeDiamond.hh \
    include/XLogicalAtomicLatticeSingleAtom.hh \
    include/XLogicalBase.hh \
    include/XLogicalLattice.hh \
    include/XPhysicalLattice.hh \
    include/XUnitCell.hh \
    include/XVCrystalCharacteristic.hh \
    include/XVCrystalIntegratedDensity.hh \
    include/XVCrystalPlanarAnalytical.hh \
    include/XWrapperContinuousDiscreteProcess.hh \
    include/XWrapperDiscreteProcess.hh \
    include/ExExChSteppingAction.hh



