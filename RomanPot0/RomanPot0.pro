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
    main.cc \
    src/DetectorConstruction.cc \
    src/EventAction.cc \
    src/PrimaryGeneratorAction.cc \
    src/RunAction.cc \
    src/SteppingAction.cc

DISTFILES += \
    run.mac \
    vis.mac \
    runAll.bash

HEADERS += \
    include/Constants.hh \
    include/DetectorConstruction.hh \
    include/EventAction.hh \
    include/PrimaryGeneratorAction.hh \
    include/RunAction.hh \
    include/SteppingAction.hh


