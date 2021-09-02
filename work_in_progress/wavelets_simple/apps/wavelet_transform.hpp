// ============================================================================
// Wavelet Transform - Simple implementation of DWT
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
// 2021-08-29 Ljubomir Kurij <ljubomir_kurij@protonmail.com
//
// * app.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// * For various numerical recipes see reference at:
//   <http://www.numerical.recipes/>.
//
// * For filesystem operations (C++17) visit 'filesystem' reference at:
//   <https://en.cppreference.com/w/cpp/filesystem>.
//
// ============================================================================


#ifndef WAVELET_TRANSFORM_HPP
#define WAVELET_TRANSFORM_HPP

// ============================================================================
// Headers include section
// ============================================================================

// "C" system headers

// Standard Library headers
#include <cmath>       // required by floor, log, pow, ...
#include <string>      // self explanatory ...
#include <vector>      // self explanatory ...


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
// Utility functions section
// ============================================================================

bool is_power_of_two(double N)
{
    // Calculate exponent first and then calculate the floor of calculated
    // exponent. For integer exponents (if N = 2^exponent) floor value will be
    // equal to exponent.
    double exponent = std::floor(std::log(N) / std::log(2.0));

    return std::pow(2, exponent) == N;
}


// ============================================================================
// Utility classes section
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// class Exception
//
// TODO: Put class description here
//
///////////////////////////////////////////////////////////////////////////////

class Exception {
protected:
    std::string message_;

public:
    Exception() : message_("General exception!") {}
    Exception(std::string message) : message_(message) {}
    ~Exception() {}
    std::string message() const { return message_; }
};


// ============================================================================
// Wavelet classes
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// class Wavelet
//
// TODO: Put class description here
//
///////////////////////////////////////////////////////////////////////////////

class Wavelet {
public:
    ///////////////////////////////////////////////////////////////////////////
    //
    // Constructors and Destructor
    //
    ///////////////////////////////////////////////////////////////////////////
    Wavelet() {}
    ~Wavelet() {}

    ///////////////////////////////////////////////////////////////////////////
    //
    // Class exceptions
    //
    ///////////////////////////////////////////////////////////////////////////
    class BuffersSizeMismatch : public Exception {
    public:
        BuffersSizeMismatch(std::string message)
            : Exception("Data buffers size mismatch!") {}
        ~BuffersSizeMismatch() {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    // Virtual methods
    //
    ///////////////////////////////////////////////////////////////////////////
    virtual void forwardTransform(
            const std::vector<double> &data,
            std::vector<double> &dest,
            const unsigned int order
            ) = 0;
    virtual void inverseTransform(
            const std::vector<double> &data,
            std::vector<double> &dest,
            const unsigned int order
            ) = 0;
    virtual void pre_condition(
            const std::vector<double> &data,
            const unsigned int data_size
            ) {}
    virtual void post_condition(
            const std::vector<double> &data,
            const unsigned int data_size
            ) {}

};


///////////////////////////////////////////////////////////////////////////////
//
// class Daub4
//
// TODO: Put class description here
//
///////////////////////////////////////////////////////////////////////////////

class Daub4 : Wavelet {
public:
    static std::vector<double> C_ {
        0.4829629131445341,
        0.8365163037378077,
        0.2241438680420134,
        -0.1294095225512603
    };

public:
    ///////////////////////////////////////////////////////////////////////////
    //
    // Constructors and Destructor
    //
    ///////////////////////////////////////////////////////////////////////////
    Daub4() {}
    ~Daub4() {}

    ///////////////////////////////////////////////////////////////////////////
    //
    // Public methods
    //
    ///////////////////////////////////////////////////////////////////////////
    void forwardTransform(
            const std::vector<double> &data,
            std::vector<double> &dest,
            const unsigned int order
            ) {
        // Do some basic sanity checks first
        if(data.size() != dest.size()) throw BufferSizeMismatch();

        unsigned int offset, i, j;

        for(i=0,j=0; j<order-3; j+=2,i++) {
            dest[i] = C_[0]*data[j]
                + C_[1]*data[j+1]
                + C_[2]*data[j+2]
                + C_[3]*data[j+3];
            dest[i+offset] = C_[3]*data[j]
                - C_[2]*data[j+1]
                + C_[1]*data[j+2]
                - C_[0]*data[j+3];

        }

        dest[i] = C_[0]*data[order-2]
            + C_[1]*data[order-1]
            + C_[2]*data[0]
            + C_[3]*data[1];
        dest[i+offset] = C_[3]*data[order-2]
            - C_[2]*data[order-1]
            + C_[1]*data[0]
            - C_[0]*data[1];

    }

    void inverseTransform(
            const std::vector<double> &data,
            std::vector<double> &dest,
            const unsigned int order
            ) {
        // Do some basic sanity checks first
        if(data.size() != dest.size()) throw BufferSizeMismatch();

        unsigned int offset, i, j;

        dest[0] = C_[2]*data[offset-1]
            + C_[1]*data[order-1]
            + C_[0]*data[0]
            + C_[3]*data[offset];
        dest[1] = C3*a[offset-1]
            -C0*a[order-1]
            +C1*a[0]
            -C2*a[offset];

        for(i=0,j=2; j<offset-1; i++) {
            dest[j++] = C_[2]*data[i]
                + C_[1]*data[i+offset]
                + C_[0]*data[i+1]
                + C_[3]*data[i+offset+1];
            dest[j++] = C_[3]*data[i]
                - C_[0]*data[i+offset]
                + C_[1]*data[i+1]
                - C_[2]*data[i+offset+1];

        }

    }

};


///////////////////////////////////////////////////////////////////////////////
//
// class WaveletTransform
//
// TODO: Put class description here
//
///////////////////////////////////////////////////////////////////////////////

class WaveletTransform {
private:
    Wavelet w_;
    enum Operation {ForwardTransform, InverseTransform};

public:
    ///////////////////////////////////////////////////////////////////////////
    //
    // Constructors and Destructor
    //
    ///////////////////////////////////////////////////////////////////////////
    WaveletTransform() {}
    WaveletTransform(const Wavelet &w) : w_(w) {}
    ~WaveletTransform() {}

    ///////////////////////////////////////////////////////////////////////////
    //
    // Class exceptions
    //
    ///////////////////////////////////////////////////////////////////////////
    class WrongDataSize : public Exception {
    public:
        WrongDataSize(std::string message)
            : Exception(message) {}
        ~WrongDataSize() {}
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    // Public methods
    //
    ///////////////////////////////////////////////////////////////////////////
    std::vector<double> forwardTransform(const std::vector<double> &data) {
        return transform(data, WaveletTransform::ForwardTransform);
    }

    std::vector<double> inverseTransform(const std::vector<double> &data) {
        return transform(data, WaveletTransform::inverseTransform);
    }

private:
    ///////////////////////////////////////////////////////////////////////////
    //
    // Private methods
    //
    ///////////////////////////////////////////////////////////////////////////
    std::vector<double> transform(
            const std::vector<double> &data,
            WaveletTransform::Operation op) {
        unsigned int data_size = data.size();

        if(4 > data_size) {
            WrongDataSize error {"Too few data points (<4)!"};
            throw error;
        } else if(!is_power_of_two(data_size)) {
            WrongDataSize error {
                "Size of the data vector must be power of two! \
                    (e.g. 4, 8, 16, ...)"
            };
            throw error;
        }

        std::vector<double> result(data_size, 0.0);

        if(WaveletTransform::ForwardTransform == op) {
            unsigned int counter = data_size;

            w_.pre_condition(data, data_size);
            for(; counter>=4; counter>>=1) {
                w_.forwardTransform(data, result, counter);
            }
        } else {
            unsigned int counter = 4;

            for(; counter<=data_size; counter<<=1) {
                w_.inverseTransform(data, result, counter);
            }
            w_.post_condition(data, data_size);
        }

        return result;
    }

};


#endif  // WAVELET_TRANSFORM_HPP
