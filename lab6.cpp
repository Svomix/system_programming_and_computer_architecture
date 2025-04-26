#include <iostream>

void output(double x)
{
    std::cout << x << std::endl;
}

void output(double x, bool div_zero)
{
    if (div_zero)
        std::cout << "ASM Error: dividing by zero\n";
    std::cout << x << std::endl;
}

double input()
{
    double res = 0;
    while (!(std::cin >> res) || std::cin.peek() != '\n')
    {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Incorrect input\n";
        std::cout << "Enter the num\n";
    }
    return res;
}

double cpp_func(const double a, const double b)
{
    double x;
    if (a > b)
    {
        double divider = b + 5;
        if (!divider)
        {
            std::cout << "CPP Error: dividing by zero\n";
            return 0;
        }
        x = a / divider - 10;
        return x;
    }
    else if (a == b)
    {
        x = 51;
        return x;
    }
    if (a == 0)
    {
        std::cout << "CPP Error: dividing by zero\n";
        return 0;
    }
    x = (a * b - 14 * b) / a;
    return x;
}

void asm_func(const double a, const double b)
{
    bool div_zero = 0;
    const double n14 = 14;
    const double five = 5;
    const double ten = 10;
    const double n51 = 51;
    double x = 0;
    __asm
    {
        finit; init
        fld a; st(0) = a
        fld b; st(1) = a st(0) = b
        fcomi st(0), st(1)
        jb a_bigger
        je equal
        fmul; st(0) = a * b
        fld b; st(2) = a st(1) = a * b st(0) = b
        fmul n14; st(2) = a st(1) = a * b st(0) = b * 14
        fsubp st(1), st; st(1) = a st(0) = a * b - b * 14
        fld a; st(2) = a st(1) = a * b - b * 14; st(0) = a
        ftst
        fstsw ax
        sahf
        jz div_zer
        fdiv; (a* b - b * 14) / a
        jmp end
        a_bigger :
        fadd five; st(1) = a st(0) = b + 5
            ftst
            fstsw ax
            sahf
            jz div_zer
            fdiv; st(1) = a st(0) = a / (b + 5)
            fsub ten; st(1) = a st(0) = a / (b + 5) - 10
            jmp end
            equal :
        fld n51; st(2) = a st(1) = b st(0) = 51
            fst x
            jmp ex
            div_zer:
            mov div_zero, 1
             end :
           fstp x
            ex :
    }
    output(x, div_zero);
}


int main()
{
    double a;
    double b;
    while (true)
    {
        std::cout << "Input a:\n";
        a = input();
        std::cout << "Input b:\n";
        b = input();
        std::cout << "CPP result:\n";
        output(cpp_func(a, b));
        std::cout << "ASM result:\n";
        asm_func(a, b);
    }
}
