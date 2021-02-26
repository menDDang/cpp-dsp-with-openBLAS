#pragma once

// Include headers
#include <cmath>
#include "math/constants.h"


namespace math {

template <typename T>
class Complex {

public:

    // Default Constructors
    Complex(T real=0, T image=0) : m_real(real), m_image(image) 
    {

    }

    // Copy Constructor
    Complex(Complex& other) : m_real(other.real), m_image(other.image)
    {

    }

    // Destructor
    ~Complex()
    {

    }

protected:

    // Real part of complex number
    T m_real;       

    // Imaginary part of comlex number
    T m_image;

public:

    // Get real value
    inline T real() const { return m_real; }
    
    // Get image value
    inline T image() const { return m_image; }

    // Get absolute value of complex number (i.e. real^2 + image^2)
    inline T abs() const
    {
        return (m_real * m_real) + (m_image * m_image);
    }

    // Get raiuds
    inline T radius() const
    {
        return std::sqrt(abs());
    }

    // Get angle
    inline T angle()
    {
        return std::atan2(m_image, m_real);
    }

    // Complex conjugate
    Complex conjugate() const 
    {
        return Complex(m_real, -1 * m_image);
    }

    // Operations
    Complex operator+ (const Complex& other) const
    {
        T real = m_real + other.m_real;
        T image = m_image + other.m_image;
        return Complex(real, image);
    }

    Complex operator- (const Complex& other) const
    {
        T real = m_real - other.m_real;
        T image = m_image - other.m_image;
        return Complex(real, image);
    }

    Complex operator* (const Complex& other) const
    {
        T real = (m_real * other.m_real) - (m_image * other.m_image);
        T image = (m_real * other.m_image) + (m_image * other.m_real);
        return Complex(real, image);
    }

    Complex operator/ (const Complex& other) const
    {
        T denomiator = (other.m_real * other.m_real) + (other.m_image * other.m_image);
        denomiator = (denomiator == 0) ? EPSILON : denomiator;  // prevent to devide by 0
        return (*this) * other / denomiator;
    } 

    Complex operator+ (T realNumber) const { return this->operator+(Complex(realNumber, 0)); }
    Complex operator- (T realNumber) const { return this->operator-(Complex(realNumber, 0)); }
    Complex operator* (T realNumber) const { return this->operator*(Complex(realNumber, 0)); }
    Complex operator/ (T realNumber) const { return this->operator/(Complex(realNumber, 0)); }

    // Assginment operation
    Complex& operator= (Complex& other) 
    {
        m_real = other.m_real;
        m_image = other.m_image;
        return *this;
    }

    Complex& operator+= (const Complex& other)
    {
        m_real += other.m_real;
        m_image += other.m_image;
        return *this;
    }

    Complex& operator-= (const Complex& other)
    {
        m_real -= other.m_real;
        m_image -= other.m_image;
        return *this;
    }

    Complex& operator*= (const Complex& other)
    {        
        T real = (m_real * other.m_real) - (m_image * other.m_image);
        T image = (m_real * other.m_image) + (m_image * other.m_real);
        m_real = real;
        m_image = image;
        return *this;
    }

    Complex& operator/= (const Complex& other)
    {
        T denomiator = (other.m_real * other.m_real) + (other.m_image * other.m_image);
        denomiator = (denomiator == 0) ? EPSILON : denomiator;  // prevent to devide by 0

        m_real /= denomiator;
        m_image /= denomiator;
        return this->operator*=(other);
    } 
    
    Complex operator+= (T realNumber) const { return this->operator+=(Complex(realNumber, 0)); }
    Complex operator-= (T realNumber) const { return this->operator-=(Complex(realNumber, 0)); }
    Complex operator*= (T realNumber) const { return this->operator*=(Complex(realNumber, 0)); }
    Complex operator/= (T realNumber) const { return this->operator/=(Complex(realNumber, 0)); }

};


template <typename T>
inline Complex<T> add(Complex<T>& a, Complex<T>& b) { return a + b; }

template <typename T>
inline Complex<T> subtract(Complex<T>& a, Complex<T>& b) { return a - b; }

template <typename T>
inline Complex<T> multiply(Complex<T>& a, Complex<T>& b) { return a * b; }

template <typename T>
inline Complex<T> devide(Complex<T>& a, Complex<T>& b) { return a / b; }

template <typename T>
inline T abs(Complex<T>& z) { return z.abs(); }

template <typename T>
inline T sqrt(Complex<T>& z) { return z.radius; }

// Convert radius & angle values into complex number
template <typename T>
Complex<T> angle2complex(T radius, T angle)
{
    T real = radius * std::cos(angle);
    T image = radius * std::sin(angle);
    return Complex(real, image);
}

}  // end of namespace 'math'