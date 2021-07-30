// ============================================================================
//
// Physics coherent physical constants
//
//  Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This code, "physical_constants.hpp", is a derivate of "PhysicalConstants.h"
// code by M.Maire from software released by CLHEP project under GNU
// LGPLv3 license. You can find CLHEP project source code along with license
// information below. We acknowledge and are grateful to devleopers of the
// CLHEP project for their contributions to open source.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// ============================================================================


// ============================================================================
//
// Documentation:
//
// 2021-07-30 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * added: relative air humidity value for standard amospheric conditions.
//
// 2021-07-29 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * physical_constants.hpp: created from SystemOfUnits.h.
//
//
// * The basic units are :
//      millimeter              (millimeter)
//      nanosecond              (nanosecond)
//      Mega electron Volt      (MeV)
//      positron charge         (eplus)
//      degree Kelvin           (kelvin)
//      the amount of substance (mole)
//      luminous intensity      (candela)
//      radian                  (radian)
//      steradian               (steradian)
//
//   Below is a non exhaustive list of Physical CONSTANTS, computed in the
//   Internal Physics System Of Units. You can add your own constants.
//
// ============================================================================


// ============================================================================
//
// Credits:
//
// * CLHEP <https://proj-clhep.web.cern.ch/proj-clhep/>
//   Copyright (C) 1996-2021 CLHEP project. All rights reserved.
//   License (GNU LGPLv3) <http://www.gnu.org/licenses/lgpl-3.0.txt>
//
// ============================================================================


#ifndef PHYS_PHYSICAL_CONSTANTS_H
#define PHYS_PHYSICAL_CONSTANTS_H

#include "system_of_units.hpp"

namespace PHYSICS {
    ///////////////////////////////////////////////////////////////////////////
    //
    //  Avogadro's number
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double Avogadro = 6.02214179e+23/mole;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Speed of light
    //
    //      c   = 299.792458 mm/ns
    //      c^2 = 898.7404 (mm/ns)^2
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double c_light   = 2.99792458e+8 * m/s;
    static const double c_squared = c_light * c_light;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Planck's constant
    //
    //      h     = 4.13566e-12 MeV*ns
    //      hbar  = 6.58212e-13 MeV*ns
    //      hbarc = 197.32705e-12 MeV*mm
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double h_Planck      = 6.62606896e-34 * joule*s;
    static const double hbar_Planck   = h_Planck/twopi;
    static const double hbarc         = hbar_Planck * c_light;
    static const double hbarc_squared = hbarc * hbarc;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Electron charge
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double electron_charge = - eplus; // see SystemOfUnits.h
    static const double e_squared = eplus * eplus;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  AMU
    //
    //      amu_c2 - atomic equivalent mass unit
    //             - AKA, unified atomic mass unit (u)
    //      amu    - atomic mass unit
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double electron_mass_c2 = 0.510998910 * MeV;
    static const double   proton_mass_c2 = 938.272013 * MeV;
    static const double  neutron_mass_c2 = 939.56536 * MeV;
    static const double           amu_c2 = 931.494028 * MeV;
    static const double              amu = amu_c2/c_squared;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Permeability
    //
    //      permeability of free space mu0    = 2.01334e-16 Mev*(ns*eplus)^2/mm
    //      permittivity of free space epsil0 = 5.52636e+10 eplus^2/(MeV*mm)
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double mu0      = 4.0*pi*1.0e-7 * henry/m;
    static const double epsilon0 = 1.0/(c_squared*mu0);


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Electromagnetic coupling
    //
    //      electromagnetic coupling = 1.43996e-12 MeV*mm/(eplus^2)
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double elm_coupling            = e_squared/(4.0*pi*epsilon0);
    static const double fine_structure_const    = elm_coupling/hbarc;
    static const double classic_electr_radius   = elm_coupling/electron_mass_c2;
    static const double electron_Compton_length = hbarc/electron_mass_c2;
    static const double Bohr_radius             = electron_Compton_length
                                                    /fine_structure_const;

    static const double alpha_rcl2 = fine_structure_const
                                       *classic_electr_radius
                                       *classic_electr_radius;

    static const double twopi_mc2_rcl2 = twopi*electron_mass_c2
                                                 *classic_electr_radius
                                                 *classic_electr_radius;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Boltzmann's constant
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double k_Boltzmann = 8.617343e-11 * MeV/kelvin;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Standard atmospheric conditions
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double STP_Temperature = 273.15*kelvin;
    static const double STP_Pressure    = 1.0*atmosphere;
    static const double STP_RH          = 50.0*RH;
    static const double kGasThreshold   = 10.0*mg/cm3;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Universe mean density
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double universe_mean_density = 1.0e-25*g/cm3;

}  // namespace PHYSICS

#endif /* PHYS_PHYSICAL_CONSTANTS_H */
