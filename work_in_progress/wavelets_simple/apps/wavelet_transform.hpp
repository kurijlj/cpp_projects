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
// Utility function section
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
    class WTException {
    protected:
        std::string message_;

    public:
        WTException() : message_("") {}
        WTException(std::string message) : message_(message) {}
        ~WTException() {}
        std::string message() const { return message_; }
    };

    class WrongDataSize : public WTException {
    public:
        WrongDataSize(std::string message)
            : WTException(message) {}
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


// void wt1(std::vector<double> &data, const Int isign, Wavelet &wlet)
// {
//     Int nn, n=a.size();
//     if (n < 4) return;
//     if (isign >= 0) {
//         wlet.condition(a,n,1);
//         for (nn=n;nn>=4;nn>>=1) wlet.filt(a,nn,isign);
//     } else {
//         for (nn=4;nn<=n;nn<<=1) wlet.filt(a,nn,isign);
//         wlet.condition(a,n,-1);
//     }
// }


#endif  // WAVELET_TRANSFORM_HPP
