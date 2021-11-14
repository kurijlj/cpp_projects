// ============================================================================
//
// Ray Tracer - Simple ray tracing engine
//
//  Copyright (C) 2021 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
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
// 2021-11-12 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
//
// * ray_tracer.hpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For on how to develop your own ray tracer visit page at
//   <https://raytracing.github.io/>
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// * For command line arguments parsing using clipp consult documentation and
//   examples at <https://github.com/muellan/clipp>.
//
// * For filesystem operations (C++17) visit 'filesystem' reference at:
//   <https://en.cppreference.com/w/cpp/filesystem>.
//
// * For refrence on badbit, failbit, eofbit visit:
//   <https://gehrcke.de/2011/06/reading-files-in-c-using-ifstream-dealing
//    -correctly-with-badbit-failbit-eofbit-and-perror/>
//
// ============================================================================


#ifndef RAY_TRACER_HPP_
#define RAY_TRACER_HPP_

// ============================================================================
// Headers include section
// ============================================================================

#include <cmath>    // required by sqrt
// #include <iostream>  // required by cin. cout, 
#include <string>   // self explanatory ..
#include <sstream>  // required by stringstream


// ============================================================================
// Define namespace aliases
// ============================================================================


// ============================================================================
// Global constants section
// ============================================================================


// ============================================================================
// Global variables section
// ============================================================================


// ============================================================================
// Ray Tracer Classes
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// Data Structures Classes
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// class Vector3D
//
// TODO: Put class description here
//
//
///////////////////////////////////////////////////////////////////////////////


class Vector3D {
private:
    double e[3];

public:
    Vector3D() : e{0,0,0} {}
    Vector3D(double e1, double e2, double e3) : e{e1, e2, e3} {}

    double e1() const { return e[0]; }
    double e2() const { return e[1]; }
    double e3() const { return e[2]; }

    Vector3D operator-() const { return Vector3D(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    Vector3D& operator+=(const Vector3D &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;

    }

    Vector3D& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;

    }

    Vector3D& operator/=(const double t) {
        return *this *= 1/t;

    }

    double length() const {
        return std::sqrt(length_squared());

    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];

    }

    std::string str() {
        std::stringstream buf;

        buf << "Vector3D(e1: " << e[0]
            << ", e2: " << e[1]
            << ", e3: " << e[2]
            << ")";

        return buf.str();

    }

};


class Voxel {
private:
    long int e[3];  // Voxel coordinates
    double val;     // Voxel value (intensity)

public:
    Voxel() : e{0,0,0}, val(0.0) {}
    Voxel(long int x, long int y, long int z, double value)
        : e{x, y, z}, val(value) {}

    long int x() const { return e[0]; }
    long int y() const { return e[1]; }
    long int z() const { return e[2]; }
    double value() const { return val; }

    Voxel& operator+=(const Voxel &v) {
        if(e[0] == v.e[0]
                && e[1] == v.e[1]
                && e[2] == v.e[2]) {
            val += v.value();

        }

        return *this;

    }

    Voxel& operator*=(const double t) {
        if(e[0] == v.e[0]
                && e[1] == v.e[1]
                && e[2] == v.e[2]) {
            val *= v.value();

        }

        return *this;

    }

    Voxel& operator/=(const double t) {
        return *this *= 1/t;

    }

    std::string str() {
        std::stringstream buf;

        buf << "Voxel(x: " << e[0]
            << ", y: " << e[1]
            << ", y: " << e[2]
            << ", value: " << val
            << ")";

        return buf.str();

    }


};


///////////////////////////////////////////////////////////////////////////////
//
// Vector3D Utility Functions
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// function operator+
//
// Returns sum Vector3D of two vectors.
//
//
///////////////////////////////////////////////////////////////////////////////

inline Vector3D operator+(const Vector3D &u, const Vector3D &v) {
    return Vector3D(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);

}


///////////////////////////////////////////////////////////////////////////////
//
// function operator-
//
// Returns Vector3D difference of two vectors.
//
//
///////////////////////////////////////////////////////////////////////////////

inline Vector3D operator-(const Vector3D &u, const Vector3D &v) {
    return Vector3D(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);

}


///////////////////////////////////////////////////////////////////////////////
//
// function operator*
//
// Returns multiplied parts e1, e2, and e3 of two Vectors3D.
//
//
///////////////////////////////////////////////////////////////////////////////

inline Vector3D operator*(const Vector3D &u, const Vector3D &v) {
    return Vector3D(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);

}


///////////////////////////////////////////////////////////////////////////////
//
// function operator*
//
// Returns Vector3D multiplied by a scalar.
//
//
///////////////////////////////////////////////////////////////////////////////

inline Vector3D operator*(double t, const Vector3D &v) {
    return Vector3D(t*v.e[0], t*v.e[1], t*v.e[2]);

}


///////////////////////////////////////////////////////////////////////////////
//
// function operator*
//
// Returns Vector3D multiplied by a scalar.
//
//
///////////////////////////////////////////////////////////////////////////////


inline Vector3D operator*(const Vector3D &v, double t) {
    return t * v;

}


///////////////////////////////////////////////////////////////////////////////
//
// function operator/
//
// Returns Vector3D divided by a scalar.
//
//
///////////////////////////////////////////////////////////////////////////////

inline Vector3D operator/(Vector3D v, double t) {
    return (1/t) * v;

}


///////////////////////////////////////////////////////////////////////////////
//
// function dot
//
// Returns dot product of two Vector3D vectors.
//
//
///////////////////////////////////////////////////////////////////////////////

inline double dot(const Vector3D &u, const Vector3D &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];

}


///////////////////////////////////////////////////////////////////////////////
//
// function cross
//
// Returns cross product of two Vector3D vectors.
//
//
///////////////////////////////////////////////////////////////////////////////

inline Vector3D cross(const Vector3D &u, const Vector3D &v) {
    return Vector3D(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);

}


///////////////////////////////////////////////////////////////////////////////
//
// function unit_vector
//
// Returns the unit vector of a Vector3D.
//
//
///////////////////////////////////////////////////////////////////////////////

inline Vector3D unit_vector(Vector3D v) {
    return v / v.length();

}


#endif  // RAY_TRACER_HPP_
