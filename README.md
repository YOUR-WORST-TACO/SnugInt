# SnugInt
A safe integer addition library written for use with C++ 14.
## Philosophy
C and C++ are fundamentally flawed due to specific vulnerabilities present in both languages.
one such vulnerability is Integer overflow, or the process of integer memory going outside of its allocated space

an example of such an overflow would be something like the following:
```objectivec
unsigned int a = 12;
unsigned int b = 13;
unsigned int c = a - b;
```
what we would expect is that the value of C would be 0, as an unsigned number cannot be negative.
Instead we end up with the value of `4,294,967,295` in `c` and this is due to the memory wrapping 
and swapping memory it should not have access to. 

this can ultimately cause unpredictable behavior from your programs which is undesirable and should be prevented.
To combat such issues, I wrote this proof of concept library based on the idea of pre and post integer checks.
## Building
```bash
cmake .
make
sudo make install
```

## Usage
SnugInt is intended to be used to prevent integer overflow as seen in the example below
```objectivec
try
{   // perform the operation
    SnugInt<unsigned int> si1 = 1;
    SnugInt<unsigned int> si2 = 10;
    si1 = si1 - si2;
} catch (std::exception& e)
{
    // handle the exception
}
```
SnugInt can also be used to perform safe integer operations with similar types
```objectivec
try
{
    SnugInt<long> si1 = 1000000;
    long l2 = 100000;
    si1 = si1 * l2;
} catch (std::exception& e)
{
    // handle the exception    
}
```

## Exceptions
You can use the exceptions like this to make detecting and handling more specific.
```objectivec
try
{
    // SnugInt operation
} catch (SnugInt_Type_Mismatch_Exception& e)
{
    // handle the type mismatch exception
}
```
There are the following exceptions

```
SnugInt_Addition_Overflow_Exception
    called when overflow during addition is preditcted
 
SnugInt_Addition_Underflow_Exception
    called when undeflow during addition is predicted
 
SnugInt_Subtraction_Overflow_Exception
    called when overflow during subtraction is predicted
 
SnugInt_Subtraction_Underflow_Exception
    called when underflow during subtraction is predicted
 
SnugInt_Multiplication_Overflow_Exception
    called when overflow during multiplication is predicted
 
SnugInt_Multiplication_Underflow_Exception
    called when underflow during multiplication is predicted
 
SnugInt_Size_Mismatch_Exception
    called when a size mismatch during assignment is detected
 
SnugInt_Type_Mismatch_Exception
    called when an unsupported type is used during assignment
```

## License
This project is licensed under the Apache License Version 2.0 - See the [LICENSE](LICENSE) file for details
