#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4NistManager.hh"
#include "globals.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "Constants.hh"
#include "G4ThreeVector.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nistManager = G4NistManager::Instance();

//    G4Material* AIR         = nistManager->FindOrBuildMaterial("G4_AIR");
    G4Material* TUNGSTEN    = nistManager->FindOrBuildMaterial("G4_W");
    G4Material* VACUUM      = nistManager->FindOrBuildMaterial("G4_Galactic");

    // WORLD
    G4Box* world_box = new G4Box("world",
                                 Constants::world_dim_x/2,
                                 Constants::world_dim_y/2,
                                 Constants::world_dim_z/2);
    G4LogicalVolume* world_log = new G4LogicalVolume(world_box, VACUUM, "world");
    G4VPhysicalVolume* world_phys = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), world_log, "world", 0, false, 0);

    // RomanPot0
    G4Box* rp0_box = new G4Box("target",
                                      Constants::rp0_dim_x/2,
                                      Constants::rp0_dim_y/2,
                                      Constants::rp0_dim_z/2);
    G4LogicalVolume* rp0_log = new G4LogicalVolume(rp0_box, TUNGSTEN, "target");
    new G4PVPlacement(0,G4ThreeVector(Constants::rp0_pos_x-Constants::rp0_dim_x/2,
                                      Constants::rp0_pos_y,
                                      Constants::rp0_pos_z),rp0_log, "septum", world_log, false, 0);

    rp0_log->SetVisAttributes(G4VisAttributes(G4Color::Brown()));

    // PHANTOM SENSITIVE PLANE
    G4Box* phantom_box = new G4Box("phantom",
                                   Constants::world_dim_x/2,
                                   Constants::world_dim_y/2,
                                   Constants::phantom_dim_z/2);

    G4LogicalVolume* phantom_log_0 = new G4LogicalVolume(phantom_box,VACUUM,"phantom_0");
    G4LogicalVolume* phantom_log_1 = new G4LogicalVolume(phantom_box,VACUUM,"phantom_1");
    new G4PVPlacement(0,G4ThreeVector(0,0, Constants::phantom_0_pos_z),phantom_log_0,"phantom_0",world_log,false,0);
    new G4PVPlacement(0,G4ThreeVector(0,0, Constants::phantom_1_pos_z),phantom_log_1,"phantom_1",world_log,false,0);

    phantom_log_0->SetVisAttributes(G4VisAttributes(G4Color::Gray()));
    phantom_log_1->SetVisAttributes(G4VisAttributes(G4Color::Gray()));

    return world_phys;
}
