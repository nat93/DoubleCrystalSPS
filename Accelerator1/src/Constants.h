#ifndef Constants_h
#define Constants_h

namespace Constants
{
// Position
const double _cry1_51652_ua9_pos    = 5130.8986;    // [m]
const double _cry2_51652_ua9_pos    = 5131.3936;    // [m]
const double _q1_51710_pos          = 5153.1727;    // [m]
const double _xrph0_51779_ua9_pos   = 5175.4259;    // [m]
const double _cry3_51799_ua9_pos    = 5180.8295;    // [m]

const double _beamAngleInitialAtCryPosition     = 4.88183e-05; // [rad]
const double _beamPositionInitialAtCryPosition  = -0.00244892;  // [m]

const double _nominal_momentum = 270.0;         // [GeV/c]
const double _crystalAngle = -301.0e-6;         // [rad]

const double _dipole_length     = 6.26;         // [m]
const double _quadrupole_length = 3.085;        // [m]
const double _sextupole_length  = 0.423;        // [m]

//Q26
/*
const double _grad_quad_1 = -0.0144394607;      // [m-2] kQD
*/

//Q20

const double _grad_quad_1 = -0.01158097147;      // [m-2] kQD

const int _order_transport_matrix = 1;

const double _aph = 0.075;                      // [m]
const double _apv = 0.075;                      // [m]

const bool _switch_magnets = true;
}

#endif
