/*
    specturm.h
    2022.2.25
*/
#pragma once
#include <eloimx/eloimx.h>
#include <algorithm>
ELX_NAMESPACE_BEGIN

struct elxSpectrum {
    float r, g, b;

    elxSpectrum() : r(.0f), g(.0f), b(.0f) {}

    elxSpectrum(float value) : r(value), g(value), b(value) {}
    
    elxSpectrum(float r, float g, float b) : r(r), g(g), b(b) {}

    elxSpectrum operator+ (const elxSpectrum &s) const {
        return elxSpectrum(r+s.r, g+s.g, b+s.b);
    }

    elxSpectrum& operator+= (const elxSpectrum &s) {
        r+=s.r; g+=s.g; b+=s.b;
        return *this;
    }

    elxSpectrum operator*(float f) const {
        return elxSpectrum(r * f, g * f, b * f);
    }

    elxSpectrum& operator*=(float f) {
        r *= f; g *= f; b *= f;
        return *this;
    }

    elxSpectrum operator/(float f) const {
        float invf = 1.0f / f;
        return elxSpectrum(r * invf, g * invf, b * invf);
    }

    elxSpectrum& operator/=(float f) {
        float invf = 1.0f / f;
        r *= invf; g *= invf; b *=invf;
        return *this;
    }

    elxSpectrum operator/(const elxSpectrum &spc) const {
        return elxSpectrum(
            r/spc.r,
            g/spc.g,
            b/spc.b
        );
    }

    elxSpectrum& operator/=(const elxSpectrum &spc) {
        *this = *this/spc;
        return *this;
    }

    elxSpectrum operator*(const elxSpectrum &spc) const {
        return elxSpectrum(r*spc.r, g*spc.g, b*spc.b);
    }

    elxSpectrum& operator*=(const elxSpectrum &spc) {
        r *= spc.r; g *= spc.g; b *= spc.b;
        return *this;
    }

    elxSpectrum operator-(const elxSpectrum &spc) const {
        return elxSpectrum(r-spc.r, g-spc.g, b-spc.b);
    }

    elxSpectrum& operator-=(const elxSpectrum &spc) {
        *this = *this - spc;
        return *this;
    }

    bool operator!=(const elxSpectrum &spc) const {
        return (r!=spc.r) || (g != spc.g) || (b != spc.b);
    }

    bool operator==(const elxSpectrum & spc) const {
        return (r==spc.r) && (g == spc.g) && (b == spc.b);
    }

    bool isZero() const {
        return *this==elxSpectrum(.0f);
    }

    float max() const {
        return std::max(std::max(r, g), b);
    }

    elxSpectrum safe_sqrt() const {
        return elxSpectrum(
            std::sqrt(r),
            std::sqrt(g),
            std::sqrt(b)
        );
    }

    std::string toString() const;

};

ELX_NAMESPACE_END