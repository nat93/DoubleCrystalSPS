#ifndef Constants_h
#define Constants_h

#include "TMath.h"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

namespace Constants
{
    const G4double world_dim_x = 100.0*mm;
    const G4double world_dim_y = 100.0*mm;
    const G4double world_dim_z = 10.0*mm;

    const G4double rp0_dim_x =  30.0*mm;
    const G4double rp0_dim_y =  50.0*mm;
    const G4double rp0_dim_z =   1.0*mm;

    const G4double rp0_window_dim_z 	=   0.3*mm;
    const G4double tpx_fr4_dim_z 	=   1.3*mm;
    const G4double tpx_pcb_dim_z 	=   0.1*mm;
    const G4double tpx_chip_dim_z 	=   0.7*mm;
    const G4double tpx_sensor_dim_z 	=   0.3*mm;

    const G4double rp0_pos_x =  -2.47114*mm - (71.45-64.72)*mm;
    const G4double rp0_pos_y =  0.0*mm;
    const G4double rp0_pos_z =  0.0*mm;

    const G4double phantom_dim_z    =  0.10*mm;
    const G4double phantom_0_pos_z  = -2*mm;
    const G4double phantom_1_pos_z  =  2*mm;

    const G4double beam_pos_z = -2.1*mm;

    const G4int rp0_type = 2; // 0 - rp0 is out, 1 - rp0 simple plate, 2 - rp0 layers
}

#endif
