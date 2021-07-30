// ============================================================================
//
// Physics coherent system of Units
//
//  Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// This code, "system_of_units.hpp", is a derivate of "SystemOfUnits.h" code
// by M.Maire and S.Giani from software released by CLHEP project under GNU
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
// * added: relative air humidity.
//
// 2021-07-29 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * added: inch, hectopascal, kilopascal, centigray, with symbols.
//
// * system_of_units.hpp: created from SystemOfUnits.h.
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
//   Below is a non exhaustive list of derived and pratical units (i.e. mostly
//   the SI units). You can add your own units.
//
//   The SI numerical value of the positron charge is defined here, as it is
//   needed for conversion factor: positron charge = e_SI (coulomb).
//
//   The others physical constants are defined in the header file:
//   physical_constants.hpp
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


#ifndef PHYS_SYSTEM_OF_UNITS_H
#define PHYS_SYSTEM_OF_UNITS_H

namespace PHYSICS {
    ///////////////////////////////////////////////////////////////////////////
    //
    //  PI
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double     pi  = 3.14159265358979323846;
    static const double  twopi  = 2*pi;
    static const double halfpi  = pi/2;
    static const double     pi2 = pi*pi;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Length [L]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double millimeter  = 1.0;
    static const double millimeter2 = millimeter*millimeter;
    static const double millimeter3 = millimeter*millimeter*millimeter;

    static const double centimeter  = 10.0*millimeter;
    static const double centimeter2 = centimeter*centimeter;
    static const double centimeter3 = centimeter*centimeter*centimeter;

    static const double meter  = 1000.0*millimeter;
    static const double meter2 = meter*meter;
    static const double meter3 = meter*meter*meter;

    static const double inch = 25.4*millimeter;  // For handling RCF scans

    static const double kilometer = 1000.0*meter;
    static const double kilometer2 = kilometer*kilometer;
    static const double kilometer3 = kilometer*kilometer*kilometer;

    static const double parsec = 3.0856775807e+16*meter;

    static const double micrometer = 1.0e-6 *meter;
    static const double  nanometer = 1.0e-9 *meter;
    static const double  angstrom  = 1.0e-10*meter;
    static const double  fermi     = 1.0e-15*meter;

    static const double      barn = 1.0e-28*meter2;
    static const double millibarn = 1.0e-3 *barn;
    static const double microbarn = 1.0e-6 *barn;
    static const double  nanobarn = 1.0e-9 *barn;
    static const double  picobarn = 1.0e-12*barn;

    // symbols
    static const double nm  = nanometer;
    static const double um  = micrometer;

    static const double mm  = millimeter;
    static const double mm2 = millimeter2;
    static const double mm3 = millimeter3;

    static const double cm  = centimeter;
    static const double cm2 = centimeter2;
    static const double cm3 = centimeter3;

    static const double m  = meter;
    static const double m2 = meter2;
    static const double m3 = meter3;

    static const double km  = kilometer;
    static const double km2 = kilometer2;
    static const double km3 = kilometer3;

    static const double pc = parsec;


    ///////////////////////////////////////////////////////////////////////////
    //
    //  Angle
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double radian      = 1.0;
    static const double milliradian = 1.0e-3*radian;
    static const double degree = (pi/180.0)*radian;

    static const double   steradian = 1.0;

    // symbols
    static const double rad  = radian;
    static const double mrad = milliradian;
    static const double sr   = steradian;
    static const double deg  = degree;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Time [T]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double nanosecond  = 1.0;
    static const double second      = 1.0e+9 *nanosecond;
    static const double millisecond = 1.0e-3 *second;
    static const double microsecond = 1.0e-6 *second;
    static const double  picosecond = 1.0e-12*second;

    static const double hertz = 1.0/second;
    static const double kilohertz = 1.0e+3*hertz;
    static const double megahertz = 1.0e+6*hertz;

    // symbols
    static const double ns = nanosecond;
    static const double  s = second;
    static const double ms = millisecond;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Electric charge [Q]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double eplus = 1. ;              // positron charge
    static const double e_SI  = 1.602176487e-19;  // positron charge in coulomb
    static const double coulomb = eplus/e_SI;     // coulomb = 6.24150 e+18 * eplus


    ///////////////////////////////////////////////////////////////////////////
    //
    // Energy [E]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double megaelectronvolt = 1.0;
    static const double     electronvolt = 1.0e-6*megaelectronvolt;
    static const double kiloelectronvolt = 1.0e-3*megaelectronvolt;
    static const double gigaelectronvolt = 1.0e+3*megaelectronvolt;
    static const double teraelectronvolt = 1.0e+6*megaelectronvolt;
    static const double petaelectronvolt = 1.0e+9*megaelectronvolt;

    static const double joule = electronvolt/e_SI;  // joule = 6.24150 e+12 * MeV

    // symbols
    static const double MeV = megaelectronvolt;
    static const double  eV = electronvolt;
    static const double keV = kiloelectronvolt;
    static const double GeV = gigaelectronvolt;
    static const double TeV = teraelectronvolt;
    static const double PeV = petaelectronvolt;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Mass [E][T^2][L^-2]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double  kilogram = joule*second*second/(meter*meter);
    static const double      gram = 1.0e-3*kilogram;
    static const double milligram = 1.0e-3*gram;

    // symbols
    static const double  kg = kilogram;
    static const double   g = gram;
    static const double  mg = milligram;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Power [E][T^-1]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double watt = joule/second;  // watt = 6.24150 e+3 * MeV/ns


    ///////////////////////////////////////////////////////////////////////////
    //
    // Force [E][L^-1]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double newton = joule/meter;  // newton = 6.24150 e+9 * MeV/mm


    ///////////////////////////////////////////////////////////////////////////
    //
    // Pressure [E][L^-3]
    //
    ///////////////////////////////////////////////////////////////////////////
#define pascal phys_pascal                           // a trick to avoid warnings
    static const double phys_pascal = newton/m2;     // pascal = 6.24150 e+3 * MeV/mm3
    static const double bar         = 100000*pascal; // bar    = 6.24150 e+8 * MeV/mm3
    static const double atmosphere  = 101325*pascal; // atm    = 6.32420 e+8 * MeV/mm3
    static const double hectopascal = 100*pascal;
    static const double kilopascal  = 1000*pascal;

    // symbols
    static const double  Pa = pascal;
    static const double hPa = hectopascal;
    static const double kPa = kilopascal;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Electric current [Q][T^-1]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double      ampere = coulomb/second;  // ampere = 6.24150 e+9 * eplus/ns
    static const double milliampere = 1.0e-3*ampere;
    static const double microampere = 1.0e-6*ampere;
    static const double  nanoampere = 1.0e-9*ampere;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Electric potential [E][Q^-1]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double megavolt = megaelectronvolt/eplus;
    static const double kilovolt = 1.0e-3*megavolt;
    static const double     volt = 1.0e-6*megavolt;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Electric resistance [E][T][Q^-2]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double ohm = volt/ampere;  // ohm = 1.60217e-16*(MeV/eplus)/(eplus/ns)


    ///////////////////////////////////////////////////////////////////////////
    //
    // Electric capacitance [Q^2][E^-1]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double farad = coulomb/volt;  // farad = 6.24150e+24 * eplus/Megavolt
    static const double millifarad = 1.0e-3*farad;
    static const double microfarad = 1.0e-6*farad;
    static const double  nanofarad = 1.0e-9*farad;
    static const double  picofarad = 1.0e-12*farad;

    ///////////////////////////////////////////////////////////////////////////
    //
    // Magnetic Flux [T][E][Q^-1]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double weber = volt*second; // weber = 1000*megavolt*ns


    ///////////////////////////////////////////////////////////////////////////
    //
    // Magnetic Field [T][E][Q^-1][L^-2]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double tesla     = volt*second/meter2;  // tesla = 0.001*megavolt*ns/mm2

    static const double gauss     = 1.0e-4*tesla;
    static const double kilogauss = 1.0e-1*tesla;

    ///////////////////////////////////////////////////////////////////////////
    //
    // Inductance [T^2][E][Q^-2]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double henry = weber/ampere;  // henry = 1.60217e-7*MeV*(ns/eplus)**2

    ///////////////////////////////////////////////////////////////////////////
    //
    // Temperature
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double kelvin = 1.0;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Amount of substance
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double mole = 1.0;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Activity [T^-1]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double becquerel = 1.0/second ;
    static const double curie = 3.7e+10 * becquerel;
    static const double kilobecquerel = 1.0e+3*becquerel;
    static const double megabecquerel = 1.0e+6*becquerel;
    static const double gigabecquerel = 1.0e+9*becquerel;
    static const double millicurie = 1.0e-3*curie;
    static const double microcurie = 1.0e-6*curie;
    static const double Bq = becquerel;
    static const double kBq = kilobecquerel;
    static const double MBq = megabecquerel;
    static const double GBq = gigabecquerel;
    static const double Ci = curie;
    static const double mCi = millicurie;
    static const double uCi = microcurie;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Absorbed dose [L^2][T^-2]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double      gray = joule/kilogram ;
    static const double  kilogray = 1.0e+3*gray;
    static const double centigray = 1.0e-2*gray;  // Commonly used in the radiotherapy
    static const double milligray = 1.0e-3*gray;
    static const double microgray = 1.0e-6*gray;

    // symbols
    static const double   Gy = gray;
    static const double  kGy = kilogray;
    static const double  cGy = centigray;
    static const double  mGy = miligray;

    ///////////////////////////////////////////////////////////////////////////
    //
    // Luminous intensity [I]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double candela = 1.0;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Luminous flux [I]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double lumen = candela*steradian;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Illuminance [I][L^-2]
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double lux = lumen/meter2;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Miscellaneous
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double per_cent     = 0.01 ;
    static const double per_thousand = 0.001;
    static const double per_million  = 0.000001;


    ///////////////////////////////////////////////////////////////////////////
    //
    // Relative air humidity (commonly used in dosimetry)
    //
    ///////////////////////////////////////////////////////////////////////////
    static const double relative_air_humidity = per_cent;

    // symbols
    static const double RH = relative_air_humidity;

}  // namespace PHYSICS

#endif /* PHYS_SYSTEM_OF_UNITS_H */
