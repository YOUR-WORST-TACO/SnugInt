//
// Created by stafoya on 3/6/2019.
//

#include "SnugInt.h"

/**
 * \brief SnugInt default constructor
 *
 * \details
 * Sets only default values for private members
 * This requires there be a proper Type
 *
 * @tparam Type SnugInt integer type
 *
 * \author Stephen Tafoya
 * \Date 3/5/2019
 */
template<class Type>
SnugInt<Type>::SnugInt()
{
    min = std::numeric_limits<Type>::min();
    max = std::numeric_limits<Type>::max();

    // Determines that our value is supported.
    if (min == max)
        throw snugint_type_mismatch;

    value = 0;
}

/**
 * \brief SnugInt copy constructor (SnugInt)
 *
 * \details
 * Takes a SnugInt other and copies value, min and max.
 * This requires the SnugInt's to be the same type.
 *
 * @tparam Type SnugInt integer type
 * @param other SnugInt to be copied
 *
 * \author Stephen Tafoya
 * \date 3/5/2019
 */
template<class Type>
SnugInt<Type>::SnugInt(const SnugInt<Type> &other)
{
    max = other.max;
    min = other.min;

    // Determines that our value is supported.
    if (min == max)
        throw snugint_type_mismatch;

    value = other.value;
}

/**
 * \brief SnugInt copy constructor (T)
 *
 * \details
 * Takes an unknown item T and attempts to assign it to value
 * Requires that T is a numerical value and that it fits into Type
 *
 * @tparam Type SnugInt integer type
 * @tparam T unknown item type
 * @param item value to be copied
 *
 * \author Stephen Tafoya
 * \date 3/10/2019
 */
template<class Type>
template<class T>
SnugInt<Type>::SnugInt(const T &item)
{
    static_assert(std::is_integral<T>::value, "Cannot assign SnugInt to a non integral type.");

    min = std::numeric_limits<Type>::min();
    max = std::numeric_limits<Type>::max();

    // Determines that our value is supported.
    if (min == max)
        throw snugint_type_mismatch;

    // Throw an error if the item will not fit in our Type
    if (item > max || item < min)
        throw snugint_size_mismatch;

    value = item;
}

/**
 * \brief SnugInt assignment operator <SnugInt>
 *
 * \details
 * Takes a SnugInt and assigns its values to value, max, min.
 * Requires the SnugInt's type to be the same
 *
 * @tparam Type SnugInt integer type
 * @param other SnugInt to be assigned from
 * @return resulting SnugInt object
 *
 * \author Stephen Tafoya
 * \date 3/5/2019
 */
template<class Type>
SnugInt<Type>& SnugInt<Type>::operator=(const SnugInt<Type> &other)
{
    value = other.value;
    max = other.max;
    min = other.min;

    return *this;
}

/**
 * \brief SnugInt assignment operator <Type>
 *
 * \details
 * Takes a Type variable and assigns its value to value and finds the max and min.
 * Requires that other be of type Type
 *
 * @tparam Type SnugInt integer type
 * @param other unknown variable to assign the value of
 * @return resulting SnugInt object
 *
 * \author Stephen Tafoya
 * \date 3/5/2019
 */
template<class Type>
SnugInt<Type> &SnugInt<Type>::operator=(const Type &other) {
    value = other;
    return *this;
}

/**
 * \brief SnugInt addition assignment operator (SnugInt, SnugInt)
 *
 * \details
 * Calls SafeAdd to perform precondition checks and addition
 *
 * @tparam Type SnugInt integer type
 * @param other the other SnugInt being add/assigned
 * @return new reference value of this + other
 */
template<class Type>
SnugInt<Type>& SnugInt<Type>::operator+=(const SnugInt<Type>& other)
{
    value = this->SafeAdd(value, other).getValue();
    return *this;
}

/**
 * \brief SnugInt addition assignment operator (SnugInt, Type)
 *
 * \details
 * Calls SafeAdd to perform precondition checks and addition
 *
 * @tparam Type SnugInt integer type
 * @param other the other Type being add/assigned
 * @return new reference value of this + other
 */
template<class Type>
SnugInt<Type>& SnugInt<Type>::operator+=(const Type& other)
{
    SnugInt<Type> temp = other;
    value = this->SafeAdd(value, temp).getValue();
    return *this;
}
/**
 * \brief SnugInt addition operator overload (SnugInt, SnugInt)
 *
 * \details
 * Calls SafeAdd to perform precondition checks and addition
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be added
 * @param right SnugInt to be added
 * @return sum of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator+(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.SafeAdd(left, right);
}

/**
 * \brief SnugInt subtraction operator overload (SnugInt, SnugInt)
 *
 * \details
 * Calls SafeSub to perform precondition checks and subtraction
 * @tparam T SnugInt integer type
 * @param left SnugInt to be subtracted from
 * @param right SnugInt to be subtracted
 * @return difference of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator-(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.SafeSub(left, right);
}

/**
 * \brief SnugInt multiplication operator overload (SnugInt, SnugInt)
 *
 * \details
 * Calls SafeMult to perform precondition checks and multiplication
 * @tparam T SnugInt integer type
 * @param left SnugInt to be multiplied
 * @param right SnugInt to be multiplied
 * @return product of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator*(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.SafeMult(left, right);
}

/**
 * \brief SnugInt division operator overload (SnugInt, SnugInt)
 *
 * \details
 * Calls SafeDiv to perform precondition checks and division
 * @tparam T SnugInt integer type
 * @param left SnugInt to be divided
 * @param right SnugInt to divide by
 * @return division of left / right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator/(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.SafeDiv(left, right);
}

/**
 * \brief SnugInt addition operator overload (SnugInt, T)
 *
 * \details
 * Calls SafeAdd to perform precondition checks and addition
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be added
 * @param right T to be added
 * @return sum of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator+(const SnugInt<T> &left, const T &right)
{
    SnugInt<T> temp(right);
    return left.SafeAdd(left, temp);
}

/**
 * \brief SnugInt subtraction operator overload (SnugInt, T)
 *
 * \details
 * Calls SafeSub to perform precondition checks and subtraction
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be subtracted from
 * @param right T to be subtracted
 * @return difference of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator-(const SnugInt<T> &left, const T &right)
{
    SnugInt<T> temp(right);
    return left.SafeSub(left, temp);
}

/**
 * \brief SnugInt multiplication operator overload (SnugInt, T)
 *
 * \details
 * Calls SafeMult to perform precondition checks and multiplication
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be multiplied
 * @param right T to be multiplied
 * @return product of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator*(const SnugInt<T> &left, const T &right)
{
    SnugInt<T> temp(right);
    return left.SafeMult(left, temp);
}

/**
 * \brief SnugInt division operator overload (SnugInt, T)
 *
 * \details
 * Calls SafeDiv to perform precondition checks and division
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be divided
 * @param right T to divide by
 * @return product of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator/(const SnugInt<T> &left, const T &right)
{
    SnugInt<T> temp(right);
    return left.SafeDiv(left, temp);
}

/**
 * \brief SnugInt addition operator overload (T, SnugInt)
 *
 * \details
 * Calls SafeAdd to perform precondition checks and addition
 *
 * @tparam T SnugInt integer type
 * @param left T to be added
 * @param right SnugInt to be added
 * @return addition of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator+(const T &left, const SnugInt<T> &right)
{
    SnugInt<T> temp(left);
    return right.SafeAdd(temp, right);
}

/**
 * \brief SnugInt subtraction operator overload (T, SnugInt)
 *
 * \details
 * Calls SafeSub to perform precondition checks and subtraction
 *
 * @tparam T SnugInt integer type
 * @param left T to be subtracted from
 * @param right SnugInt to be subtracted
 * @return difference of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator-(const T &left, const SnugInt<T> &right)
{
    SnugInt<T> temp(left);
    return right.SafeSub(temp, right);
}

/**
 * \brief SnugInt multiplication operator overload (T, SnugInt)
 *
 * \details
 * Calls SafeMult to perform precondition checks and multiplication
 *
 * @tparam T SnugInt integer type
 * @param left T to be multiplied
 * @param right SnugInt to be multiplied
 * @return product of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator*(const T &left, const SnugInt<T> &right)
{
    SnugInt<T> temp(left);
    return right.SafeMult(temp, right);
}

/**
 * \brief SnugInt division operator overload (T, SnugInt)
 *
 * \details
 * Calls SafeDiv to perform precondition checks and division
 *
 * @tparam T SnugInt integer type
 * @param left T to be divided
 * @param right SnugInt to divide by
 * @return product of left and right
 *
 * \author Stephen Tafoya
 * \date 3/9/2019
 */
template<class T>
SnugInt<T> operator/(const T &left, const SnugInt<T> &right)
{
    SnugInt<T> temp(left);
    return right.SafeDiv(temp, right);
}

/**
 * \brief SnugInt increment operator
 *
 * \details
 * Performs a simple precondition check and then increments value by 1
 *
 * @tparam Type SnugInt integer type
 * @return resulting SnugInt object
 *
 * \author Stephen Tafoya
 * \date 3/5/2019
 */
template<class Type>
SnugInt<Type>& SnugInt<Type>::operator++()
{
    if (value == max)
        throw snugint_add_overflow;

    value++;

    return *this;
}

/**
 * \brief SnugInt increment operator (int)
 *
 * \details
 * Performs a simple precondition check and then increments value by 1
 *
 * @tparam Type SnugInt integer type
 * @return resulting SnugInt object
 *
 * \author Stephen Tafoya
 * \date 3/5/2019
 */
template<class Type>
const SnugInt<Type> SnugInt<Type>::operator++(int)
{
    if (value == max)
        throw snugint_add_overflow;

    SnugInt<Type> temp = *this;
    ++*this;

    return temp;
}

/**
 * \brief SnugInt decrement operator
 *
 * \details
 * Performs a simple precondition check and then decrements value by 1
 *
 * @tparam Type SnugInt integer type
 * @return resulting SnugInt object
 *
 * \author Stephen Tafoya
 * \date 3/5/2019
 */
template<class Type>
SnugInt<Type>& SnugInt<Type>::operator--()
{
    // precondition check
    if (value == min)
        throw snugint_sub_underflow;

    value--;

    return *this;
}

/**
 * \brief SnugInt decrement operator (int)
 *
 * \details
 * Performs a simple precondition check and then decrements value by 1
 *
 * @tparam Type SnugInt integer type
 * @return resulting SnugInt object
 *
 * \author Stephen Tafoya
 * \date 3/5/2019
 */
template<class Type>
const SnugInt<Type> SnugInt<Type>::operator--(int)
{
    // precondition check
    if (value == min)
        throw snugint_sub_underflow;

    SnugInt<Type> temp = *this;
    --*this;

    return temp;
}

/**
 * \brief SnugInt LT comparison operator overload (SnugInt, SnugInt)
 *
 * \details
 * Returns the less than comparison of left.value and right.value
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator<(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.value < right.value;
}

/**
 * \brief SnugInt GT comparison operator overload (SnugInt, SnugInt)
 *
 * \details
 * Returns the greater than comparison of left.value and right.value
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator>(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.value > right.value;
}

/**
 * \brief SnugInt EQ comparison operator overload (SnugInt, SnugInt)
 *
 * \details
 * Returns the equality comparison of left.value and right.value
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator==(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.value == right.value;
}

/**
 * \brief SnugInt NEQ comparison operator overload (SnugInt, SnugInt)
 *
 * \details
 * Returns the non-equality comparison of left.value and right.value
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator!=(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.value != right.value;
}

/**
 * \brief SnugInt GTEQ comparison operator overload (SnugInt, SnugInt)
 *
 * \details
 * Returns the greater than or equal comparison of left.value and right.value
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator>=(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.value >= right.value;
}

/**
 * \brief SnugInt LTEQ comparison operator overload (SnugInt, SnugInt)
 *
 * \details
 * Returns the less than or equal comparison of left.value and right.value
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator<=(const SnugInt<T> &left, const SnugInt<T> &right)
{
    return left.value <= right.value;
}

/**
 * \brief SnugInt LT comparison operator overload (SnugInt, T)
 *
 * \details
 * Returns the less than comparison of left.value and right
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right T to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator<(const SnugInt<T> &left, const T &right)
{
    return left.value < right;
}

/**
 * \brief SnugInt GT comparison operator overload (SnugInt, T)
 *
 * \details
 * Returns the greater than comparison of left.value and right
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right T to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator>(const SnugInt<T> &left, const T &right)
{
    return left.value > right;
}

/**
 * \brief SnugInt EQ comparison operator overload (SnugInt, T)
 *
 * \details
 * Returns the equality comparison of left.value and right
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right T to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator==(const SnugInt<T> &left, const T &right)
{
    return left.value == right;
}

/**
 * \brief SnugInt NEQ comparison operator overload (SnugInt, T)
 *
 * \details
 * Returns the non-equality comparison of left.value and right
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right T to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator!=(const SnugInt<T> &left, const T &right)
{
    return left.value != right;
}

/**
 * \brief SnugInt GTEQ comparison operator overload (SnugInt, T)
 *
 * \details
 * Returns the greater than or equal comparison of left.value and right
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right T to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator>=(const SnugInt<T> &left, const T &right)
{
    return left.value >= right;
}

/**
 * \brief SnugInt LTEQ comparison operator overload (SnugInt, T)
 *
 * \details
 * Returns the less than or equal comparison of left.value and right
 *
 * @tparam T SnugInt integer type
 * @param left SnugInt to be compared
 * @param right T to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator<=(const SnugInt<T> &left, const T &right)
{
    return left.value <= right;
}

/**
 * \brief SnugInt LT comparison operator overload (T, SnugInt)
 *
 * \details
 * Returns the less than comparison of left and right.value
 *
 * @tparam T SnugInt integer type
 * @param left T to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator<(const T &left, const SnugInt<T> &right)
{
    return left < right.value;
}

/**
 * \brief SnugInt GT comparison operator overload (T, SnugInt)
 *
 * \details
 * Returns the greater than comparison of left and right.value
 *
 * @tparam T SnugInt integer type
 * @param left T to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator>(const T &left, const SnugInt<T> &right)
{
    return left > right.value;
}

/**
 * \brief SnugInt EQ comparison operator overload (T, SnugInt)
 *
 * \details
 * Returns the equality comparison of left and right.value
 *
 * @tparam T SnugInt integer type
 * @param left T to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator==(const T &left, const SnugInt<T> &right)
{
    return left == right.value;
}

/**
 * \brief SnugInt NEQ comparison operator overload (T, SnugInt)
 *
 * \details
 * Returns the non-equality comparison of left and right.value
 *
 * @tparam T SnugInt integer type
 * @param left T to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator!=(const T &left, const SnugInt<T> &right)
{
    return left != right.value;
}

/**
 * \brief SnugInt GTEQ comparison operator overload (T, SnugInt)
 *
 * \details
 * Returns the greater than or equal comparison of left and right.value
 *
 * @tparam T SnugInt integer type
 * @param left T to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator>=(const T &left, const SnugInt<T> &right)
{
    return left >= right.value;
}

/**
 * \brief SnugInt LTEQ comparison operator overload (T, SnugInt)
 *
 * \details
 * Returns the less than or equal comparison of left and right.value
 *
 * @tparam T SnugInt integer type
 * @param left T to be compared
 * @param right SnugInt to be compared
 * @return resulting comparison bool
 */
template<class T>
bool operator<=(const T &left, const SnugInt<T> &right)
{
    return left <= right.value;
}

/**
 * \brief operator overload for output buffer streams
 *
 * \details
 * Attempts to output the value of value
 *
 * @tparam T SnugInt type
 * @param os output stream
 * @param data SnugInt that will be sent into the output stream
 * @return the output stream
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
template <class T>
std::ostream &operator<<(std::ostream &os, const SnugInt<T> &data)
{
    os << data.value;
    return os;
}

/**
 * \brief operator overload for input buffer streams
 *
 * \details
 * Attempts to get the input for value
 *
 * @tparam T SnugInt type
 * @param is input stream
 * @param data SnugInt that will be sent into by the input stream
 * @return the input stream
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
template <class T>
std::istream &operator>>(std::istream &is, const SnugInt<T> &data)
{
    is >> data.value;
    return is;
}

/**
 * \brief Safely adds two SnugInts together
 *
 * \details
 * SafeAdd performs the proper precondition checks to determine
 * if it is safe to add the left value to the right value
 *
 * \details
 * a <b>SNUGINT_ADD_EXCEPTION</b> will be thrown if it is determined that overflow will occur
 *
 * @param left value to be added to right
 * @param right value to be added to left
 * @return the Sum of left and right
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
template<class Type>
SnugInt<Type> SnugInt<Type>::SafeAdd(const SnugInt<Type> &left, const SnugInt<Type> &right)
{
    if (left.value > 0 && right.value > 0)
    {   // Operation: + + + = +
        if (left.max - left.value < right.value)
        {   // throw if overflow will occur
            throw snugint_add_overflow;
        }
    } else if (left.value < 0 && right.value < 0)
    {   // Operation: - + - = -
        if (left.min - left.value > right.value)
        {   // throw if underflow will occur
            throw snugint_add_underflow;
        }
    }

    SnugInt<Type> temp(left.value + right.value);

    return temp;
}
/**
 * \brief Safely subtracts a SnugInt from another SnugInt
 *
 * \details
 * SafeSub performs the proper precondition checks to determine
 * if it is safe to subtract the right from the left
 *
 * \details
 * a <b>SNUGINT_SUB_EXCEPTION</b> will be thrown if it is determined underflow or overflow will occur
 *
 * @param left value to be subtracted from
 * @param right value to subtract
 * @return the difference of left minus right
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
template<class Type>
SnugInt<Type> SnugInt<Type>::SafeSub(const SnugInt<Type> &left, const SnugInt<Type> &right)
{
    if (left.value > 0 && right.value < 0)
    {   // Operation: + - - = +
        if (left.max - left.value < abs(right.value))
        {   // thrown if overflow will occur
            throw snugint_sub_overflow;
        }
    } else if (left.value < 0 && right.value > 0)
    {   // Operation: - - + = -
        if (abs(left.min - left.value) < right.value)
        {   // thrown if underflow will occur
            throw snugint_sub_underflow;
        }
    }

    SnugInt<Type> temp(left.value - right.value);

    return temp;
}

/**
 * \brief Safely multiplies two SnugInts together
 *
 * \details
 * SafeMult performs the proper precondition checks to determine
 * if it is safe to multiply the left and right
 *
 * \details
 * a <b>SNUGINT_MULT_EXECPTION</b> will be thrown if it is determined overflow will occur
 *
 * @param left value to be multiplied
 * @param right value to be multiplied
 * @return the product of left and right
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
template<class Type>
SnugInt<Type> SnugInt<Type>::SafeMult(const SnugInt<Type> &left, const SnugInt<Type> &right)
{
    if (left.value > 0)
    {
        if (right.value > 0)
        {   // Operands: + * + = +
            if (left.value > (left.max / right.value))
            {   // thrown if multiplication will cause overflow
                throw snugint_mult_overflow;
            }
        } else
        {   // Operands: + * - = -
            if (right.value < (left.min / left.value))
            {   // thrown if multiplication will cause underflow
                throw snugint_mult_underflow;
            }
        }
    } else
    {
        if (right.value > 0)
        {   // Operands: - * + = -
            if (left.value < (left.min / right.value))
            {   // thrown if multiplication will cause underflow
                throw snugint_mult_underflow;
            }
        } else
        {   // Operands: - * - = +
            if ((left.value != 0) && (right.value < (left.max / left.value)))
            {   // called if multiplication will cause overflow
                throw snugint_mult_overflow;
            }
        }
    }

    SnugInt<Type> temp(left.value * right.value);

    return temp;
}

/**
 * \brief Divide a SnugInt by another SnugInt
 *
 * \details
 * SafeDiv does nothing special other than dividing left by right
 *
 * @param left to be divided by right
 * @param right the divisor
 * @return resulting division
 *
 * \author Stephen Tafoya
 * \date 3/8/2019
 */
template<class Type>
SnugInt<Type> SnugInt<Type>::SafeDiv(const SnugInt<Type> &left, const SnugInt<Type> &right)
{
    SnugInt<Type> temp(left.value / right.value);
    return temp;
}