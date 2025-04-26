#include <iostream>
#include <iomanip>

double f_cpp(const double a, const double b, const double c)
{
    double divisible = 2 * b - a + b * c;
    double divider = c / 4 - 1;
    if (divider)
    {
        return divisible / divider;
    }
    std::cout << "CPP: Dividing by 0\n";
    return 0;
}

double input_double()
{
    double res = 0;
    while (!(std::cin >> res) || std::cin.peek() != '\n')
    {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Incorrect input\n";
        std::cout << "Enter the correct num\n";
    }
    return res;
}

double f_asm(const double a, const double b, const double c)
{
    bool zero = false;
    double res = 0;
    const double four = 4.0;
    const double one = 1.0;
    const double two = 2.0;
    __asm
    {
        finit
        fld c
        fdiv four
        fsub one
        ftst
        fstsw ax
        sahf
        jz div_zero
        fld b
        fmul two
        fsub a
        fld b
        fmul c
        faddp st(1), st
        fxch st(1)
        fdiv st(1), st
        fxch st(1)
        fstp res
        jmp end
        div_zero :
        mov zero, 1
            end :
    }
    if (zero)
        std::cout << "ASM Error: dividing by 0\n";
    return res;
}


int main()
{
    double a, b, c;
    while (true)
    {
        std::cout << "Enter a:\n";
        a = input_double();
        std::cout << "Enter b:\n";
        b = input_double();
        std::cout << "Enter c:\n";
        c = input_double();
        std::cout << "The result of CPP\n" << std::setprecision(20) << f_cpp(a, b, c) << std::endl;
        std::cout << "The result of ASM\n" << f_asm(a, b, c) << std::endl;
    }
}
