/*
Copyright 2019 Stephen Tafoya <stephen@tafoya.dev>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
        limitations under the License.
*/

#ifndef PROJECT_SNUGINT_H
#define PROJECT_SNUGINT_H

#include <exception>
#include <iostream>
#include <limits>

/**
 * \brief SnugInt class for safe Integer operations
 *
 * \details
 * A class designed to be used in conjunction with integral types to validate unsafe operations
 * using precondition checks. This class should be used in a try catch structure as it will throw exceptions
 * using the exception library.
 *
 * \details
 * - This class only accepts Integral types
 *
 * \details
 * - Assignment for the class accepts all types but requires the type to be a Duck Type of integrals
 *
 * \section <b>Exceptions:</b>
 * <br>The following exceptions are supported
 * \code
 *SnugInt_Addition_Overflow_Exception
 *    called when overflow during addition is preditcted
 *
 *SnugInt_Addition_Underflow_Exception
 *    called when undeflow during addition is predicted
 *
 *SnugInt_Subtraction_Overflow_Exception
 *    called when overflow during subtraction is predicted
 *
 *SnugInt_Subtraction_Underflow_Exception
 *    called when underflow during subtraction is predicted
 *
 *SnugInt_Multiplication_Overflow_Exception
 *    called when overflow during multiplication is predicted
 *
 *SnugInt_Multiplication_Underflow_Exception
 *    called when underflow during multiplication is predicted
 *
 *SnugInt_Size_Mismatch_Exception
 *    called when a size mismatch during assignment is detected
 *
 *SnugInt_Type_Mismatch_Exception
 *    called when an unsupported type is used during assignment
 * \endcode
 *
 * \section <b>Example Usage:</b>
 * \code
 *try
 *{   // perform the operation
 *    SnugInt<unsigned int> si1 = 1;
 *    SnugInt<unsigned int> si2 = 10;
 *    si1 = si1 - si2;
 *} catch (std::exception& e)
 *{
 *    // handle the exception
 *}
 * \endcode
 * @tparam Type integer to do operations with
 *
 * \author Stephen Tafoya
 * \date 3/10/2019
 */
template <class Type>
class SnugInt
{
    static_assert(std::is_integral<Type>::value, "SnugInt must be an integral");
public:
    // Constructors
    SnugInt();
    SnugInt(const SnugInt<Type> &other);
    template<class T> SnugInt(const T &item);

    // Assignment Operators
    SnugInt& operator = (const SnugInt& other);
    SnugInt& operator = (const Type& other);
    SnugInt& operator += (const SnugInt& other);
    SnugInt& operator += (const Type& other);

    // Accessor Operators
    Type getValue() { return value; };

    // Mathematical Operators (SnugInt, SnugInt)
    template<class T> friend SnugInt<T> operator+(const SnugInt<T>& left, const SnugInt<T>& right);
    template<class T> friend SnugInt<T> operator-(const SnugInt<T>& left, const SnugInt<T>& right);
    template<class T> friend SnugInt<T> operator*(const SnugInt<T>& left, const SnugInt<T>& right);
    template<class T> friend SnugInt<T> operator/(const SnugInt<T>& left, const SnugInt<T>& right);


    // Mathematical Operators (SnugInt, T)
    template<class T> friend SnugInt<T> operator+(const SnugInt<T>& left, const T& right);
    template<class T> friend SnugInt<T> operator-(const SnugInt<T>& left, const T& right);
    template<class T> friend SnugInt<T> operator*(const SnugInt<T>& left, const T& right);
    template<class T> friend SnugInt<T> operator/(const SnugInt<T>& left, const T& right);

    // Mathematical Operators (T, SnugInt)
    template<class T> friend SnugInt<T> operator+(const T& left, const SnugInt<T>& right);
    template<class T> friend SnugInt<T> operator-(const T& left, const SnugInt<T>& right);
    template<class T> friend SnugInt<T> operator*(const T& left, const SnugInt<T>& right);
    template<class T> friend SnugInt<T> operator/(const T& left, const SnugInt<T>& right);

    // Incremental & Decremental Operators
    SnugInt& operator++();
    const SnugInt operator++( int );
    SnugInt& operator--();
    const SnugInt operator--( int );

    // Comparison Operators (SnugInt, SnugInt)
    template<class T> friend bool operator< (const SnugInt<T>& left, const SnugInt<T>& right);
    template<class T> friend bool operator> (const SnugInt<T>& left, const SnugInt<T>& right);
    template<class T> friend bool operator==(const SnugInt<T>& left, const SnugInt<T>& right);
    template<class T> friend bool operator!=(const SnugInt<T>& left, const SnugInt<T>& right);
    template<class T> friend bool operator>=(const SnugInt<T>& left, const SnugInt<T>& right);
    template<class T> friend bool operator<=(const SnugInt<T>& left, const SnugInt<T>& right);

    // Comparison Operators (SnugInt, T)
    template<class T> friend bool operator< (const SnugInt<T>& left, const T& right);
    template<class T> friend bool operator> (const SnugInt<T>& left, const T& right);
    template<class T> friend bool operator==(const SnugInt<T>& left, const T& right);
    template<class T> friend bool operator!=(const SnugInt<T>& left, const T& right);
    template<class T> friend bool operator>=(const SnugInt<T>& left, const T& right);
    template<class T> friend bool operator<=(const SnugInt<T>& left, const T& right);

    // Comparison Operators (T, SnugInt)
    template<class T> friend bool operator< (const T& left, const SnugInt<T>& right);
    template<class T> friend bool operator> (const T& left, const SnugInt<T>& right);
    template<class T> friend bool operator==(const T& left, const SnugInt<T>& right);
    template<class T> friend bool operator!=(const T& left, const SnugInt<T>& right);
    template<class T> friend bool operator>=(const T& left, const SnugInt<T>& right);
    template<class T> friend bool operator<=(const T& left, const SnugInt<T>& right);

    // Stream Operators
    template <class T> friend std::ostream& operator<<(std::ostream &os, const SnugInt<T>& data);
    template <class T> friend std::istream& operator>>(std::istream &is, const SnugInt<T>& data);
private:
    Type value; /**< stored value for Type */
    Type max;   /**< max possible size for Type */
    Type min;   /**< min possible size for Type */

    // Static Precondition Safe Methods
    static SnugInt SafeAdd(const SnugInt& left, const SnugInt& right);
    static SnugInt SafeSub(const SnugInt& left, const SnugInt& right);
    static SnugInt SafeMult(const SnugInt& left, const SnugInt& right);
    static SnugInt SafeDiv(const SnugInt& left, const SnugInt& right);
};

/**
 * \brief SnugInt Exception Addition Overflow
 *
 * \details
 * This exception is thrown when a SnugInt operation detects there will be overflow from addition
 * \details
 * Throws this error to prevent overflow
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
class SnugInt_Addition_Overflow_Exception: public std::exception
{
    const char* what() const noexcept override
    {
        return "SnugInt addition operation prevented, OVERFLOW would have occurred";
    }
} snugint_add_overflow;

/**
 * \brief SnugInt Exception Addition Underflow
 *
 * \details
 * This exception is thrown when a SnugInt operation detects there will be underflow from addition
 * \details
 * Throws this error to prevent underflow
 *
 * \author Stephen Tafoya
 * \date 3/12/2019
 */
class SnugInt_Addition_Underflow_Exception: public std::exception
{
    const char* what() const noexcept override
    {
        return "SnugInt addition operation prevented, UNDERFLOW would have occurred";
    }
} snugint_add_underflow;

/**
 * \brief SnugInt Exception Subtraction Overflow
 *
 * \details
 * This exception is thrown when a SnugInt operation detects there will be overflow from subtraction
 * \details
 * Throws this error to prevent overflow
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
class SnugInt_Subtraction_Overflow_Exception: public std::exception
{
    const char* what() const noexcept override
    {
        return "SnugInt subtraction operation prevented, OVERFLOW would have occurred";
    }
} snugint_sub_overflow;

/**
 * \brief SnugInt Exception Subtraction Underflow
 *
 * \details
 * This exception is thrown when a SnugInt operation detects there will be underflow from subtraction
 * \details
 * Throws this error to prevent underflow
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
class SnugInt_Subtraction_Underflow_Exception: public std::exception
{
    const char* what() const noexcept override
    {
        return "SnugInt subtraction operation prevented, UNDERFLOW would have occurred";
    }
} snugint_sub_underflow;

/**
 * \brief SnugInt Exception Multiplication Overflow
 *
 * \details
 * This exception is thrown when a SnugInt operation detects there will be overflow from multiplication
 * \details
 * Throws this error to prevent overflow
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
class SnugInt_Multiplication_Overflow_Exception: public std::exception
{
    const char* what() const noexcept override
    {
        return "SnugInt multiplication operation prevented, OVERFLOW would have occurred";
    }
} snugint_mult_overflow;

/**
 * \brief SnugInt Exception Multiplication Underflow
 *
 * \details
 * This exception is thrown when a SnugInt operation detects there will be underflow from multiplication
 * \details
 * Throws this error to prevent underflow
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
class SnugInt_Multiplication_Underflow_Exception: public std::exception
{
    const char* what() const noexcept override
    {
        return "SnugInt multiplication operation prevented, UNDERFLOW would have occurred";
    }
} snugint_mult_underflow;

/**
 * \brief SnugInt Exception Type Size Mismatch
 *
 * \details
 * This exception is thrown when a SnugInt detects a value that will not fit
 * \details
 * Throws this error to prevent unpredictable behavior
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
class SnugInt_Size_Mismatch_Exception: public std::exception
{
    const char* what() const noexcept override
    {
        return "SnugInt Size Mismatch, Operation Failure";
    }
} snugint_size_mismatch;

/**
 * \brief SnugInt Exception Type Mismatch
 *
 * \details
 * This exception is thrown when a SnugInt detects an incompatible type
 * \details
 * Throws this error to prevent unpredictable behavior
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
class SnugInt_Type_Mismatch_Exception: public std::exception
{
    const char* what() const noexcept override
    {
        return "SnugInt Type Mismatch, Operation Failure";
    }
} snugint_type_mismatch;

#include "SnugInt.tpp"

#endif //PROJECT_SNUGINT_H
