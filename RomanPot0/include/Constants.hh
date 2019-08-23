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

    const G4double rp0_pos_x =  -2.47114*mm - (71.45-64.72)*mm;
    const G4double rp0_pos_y =  0.0*mm;
    const G4double rp0_pos_z =  0.0*mm;

    const G4double phantom_dim_z    =  0.10*mm;
    const G4double phantom_0_pos_z  = -0.75*mm;
    const G4double phantom_1_pos_z  =  0.75*mm;
}

#endif
