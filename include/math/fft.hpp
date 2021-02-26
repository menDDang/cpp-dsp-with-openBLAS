#pragma once

// Include headers
#include <cmath>
#include "error_codes.h"
#include "math/constants.h"
#include "math/complex.hpp"

namespace dsp {
namespace math {

template <typename T>
ErrorCode fft(const Complex<T>* inputs, Complex<T>* outputs, int numPoints)
{
    // Check input arguments
    if (inputs == NULL) {
    #ifdef DEBUG
        printf("math::fft - invalid argument. 'inputs' is NULL pointer.\n");
    #endif
        return ERROR_INVALID_ARGS;
    }

    if (outputs == NULL) {
    #ifdef DEBUG
        printf("math::fft - invalid argument. 'outputs' is NULL pointer.\n");
    #endif
        return ERROR_INVALID_ARGS;
    }

    if (numPoints <= 0) {
    #ifdef DEBUG
        printf("math::fft - invalid argument. 'numPoints' must be positive integer.\n");
    #endif
        return ERROR_INVALID_ARGS;
    }

    _rearrange(inputs, outputs, numPoints);
    _performFFT(outputs, numPoints, false);

    return SUCCSS;
}


/* Local functions */

// Re-arrange input complex array using bit-reversal
template <typename T>
void _rearrange(const Complex<T>* inputs, Complex<T>* outputs, int numPoints)
{
    int targetIndex = 0;
    for (int n = 0; n < numPoints; ++n) {
        // re-arrange data
        outputs[targetIndex] = inputs[n];

        // set bit mask
        int mask = numPoints;
        while (targetIndex & (mask >>= 1)) targetIndex &= ~mask;

        // apply bit mask
        targetIndex |= mask;
    }
}


// Perform in-place fast fourier transform
template <typename T>
void _performFFT(Complex<T>* x, int numPoints, bool inverse)
{
    T pi = inverse ? M_PI : -M_PI;

    // iterate through 2^n
    for (int step = 1; step < numPoints; step = (step << 1)) {
        int jump = step << 1;
        // angle increment
        T delta = pi / (T)step;
        // auxiliary sin(delta / 2)
        T sine = std::sin(delta * 0.5);
        // multiplier for trigonometric recurrence
        Complex<T> multiplier(-2.0 * sine * sine, sin(delta));
        
        // iteration through groups of different transform factor
        Complex<T> factor(1.0);
        for (int group = 0; group < step; ++group) {
            // iteration within group
            for (int pair = group; pair < numPoints; pair += jump) {
                // match position
                int match = pair + step;
                // second term of two-point transform
                Complex<T> product(factor * x[match]);
                // transform for fi + pi
                x[match] = x[pair] - product;
                // transform for fi
                x[pair] += product;
            }

            //   Successive transform factor via trigonometric recurrence
            factor = (multiplier * factor) + factor;
        }
    }
}

}  // end of namespace 'math'
}  // end of namespace 'dsp'