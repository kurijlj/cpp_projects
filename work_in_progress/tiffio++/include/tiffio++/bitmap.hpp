// ============================================================================
// <one line to give the program's name and a brief idea of what it does.>
//
//  Copyright (C) <yyyy> <Author Name> <author@mail.com>
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
// <Put documentation here>
//
// <yyyy>-<mm>-<dd> <Author Name> <author@mail.com>
//
// * <programfilename>.cpp: created.
//
// ============================================================================


// ============================================================================
//
// References (this section should be deleted in the release version)
//
// * For coding style visit Google C++ Style Guide page at
//   <https://google.github.io/styleguide/cppguide.html>.
//
// * For formatting and writting PPM image format visit:
//   <https://raytracing.github.io/books/RayTracingInOneWeekend.html>
//
// ============================================================================


#ifndef _BITMAP_HPP
#define _BITMAP_HPP


// ============================================================================
// Headers include section
// ============================================================================

// "C" system headers

// Standard Library headers
#include <vector>  // self explanatory ...

// External libraries headers

// Project headers


// ============================================================================
// BitmapObject class
// ============================================================================

template <class T>
class BitmapObject {
public:
    ///////////////////////////////////////////////////////////////////////////
    //
    // Exceptions classes
    //
    ///////////////////////////////////////////////////////////////////////////
    class BitmapObjectException {
    protected:
        std::string message_;

    public:
        BitmapObjectException() : message_("") {}
        BitmapObjectException(std::string message) : message_(message) {}
        ~BitmapObjectException() {}
        std::string message() const { return message_; }

    };

    class NotImplemented : public BitmapObjectException {
    public:
        NotImplemented() : BitmapObjectException("Not implemented!") {}
        NotImplemented(std::string message)
            : BitmapObjectException(message) {}
        ~NotImplemented() {}

    };

    class IndexOutOfLimits : public BitmapObjectException {
    public:
        IndexOutOfLimits() : BitmapObjectException("Index out of limits!") {}
        IndexOutOfLimits(std::string message)
            : BitmapObjectException(message) {}
        ~IndexOutOfLimits() {}

    };

private:
    // Attributes
    std::vector<T> pd_[4];  // pixeldata
    unsigned long w_, h_;   // width and height

public:
    // Constructors
    BitmapObject(unsigned long width, unsigned long height)
        : w_(width), h_(height) {
            pd_[0] = std::vector<T> pd_[0](width*height, 0);
            pd_[1] = std::vector<T> pd_[1](width*height, 0);
            pd_[2] = std::vector<T> pd_[2](width*height, 0);
            pd_[3] = std::vector<T> pd_[3](width*height, 0);

        }

    // Destructors
    ~BitmapObject() {}

    // Pixel access methods
    T operator()(unsigned long i, unsigned long j) const {
        if(w_ <= i || h_ <= j) {
            // Throw exception
            throw BitmapObject<T>::IndexOutOfLimits {};
        }

        unsigned long index = i + j*w_;

        return pd_[index];

    }

    T& operator()(unsigned long i, unsigned long j) const {
        if(w_ <= i || h_ <= j) {
            // Throw exception
            throw BitmapObject<T>::IndexOutOfLimits {};
        }

        unsigned long index = i + j*w_;

        return pd_.at(index);

    }

};


// ============================================================================
// BitmapObject class definitions
// ============================================================================

// ============================================================================
// BitmapObject private methods definitions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// TODO: Put method documentation here
//
///////////////////////////////////////////////////////////////////////////////


// ============================================================================
// BitmapObject public methods definitions
// ============================================================================

///////////////////////////////////////////////////////////////////////////////
//
// TODO: Put method documentation here
//
///////////////////////////////////////////////////////////////////////////////


#endif  // _BITMAP_HPP
