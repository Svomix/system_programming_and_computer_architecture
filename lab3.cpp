#include <iostream>

void output(int x)
{
    std::cout << x << std::endl;
}

void output(int x, bool div_zero, bool overflow)
{
    if (div_zero)
        std::cout << "ASM Error: dividing by zero\n";
    if (overflow)
        std::cout << "ASM Error: overflow\n";
    std::cout << x << std::endl;
}

int input()
{
    int res = 0;
    while (!(std::cin >> res) || std::cin.peek() != '\n')
    {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Incorrect input\n";
        std::cout << "Enter the num\n";
    }
    return res;
}

int cpp_func(int a, int b)
{
    int x;
    if (a > b)
    {
        int divider = b + 5;
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

int asm_func(int a, int b)
{
    bool div_zero = 0;
    bool overflow = 0;
    int x = 0;
    __asm
    {
        mov ecx, a;     ecx = a
        mov ebx, b;     ebx = b, ecx = a
        cmp ecx, ebx;   ebx = b, ecx = a
        jl smaller;     ebx = b, ecx = a
        jg greater;     ebx = b, ecx = a
        mov eax, 51;    eax = 51, ebx = b, ecx = a
        jmp save_res
        smaller :
        cmp a, 0;       ebx = b, ecx = a
            jz dividing_zero
            imul ecx, ebx; ecx = a * b, ebx = b
            jo of; ebx;    ecx = a * b, ebx = b
            imul ebx, 14;  ebx = b * 14, ecx = a * b
            jo of;          ebx = b * 14, ecx = a * b
            sub ecx, ebx;  ecx = a * b - b * 14
            jo of;
        mov eax, ecx;       eax = a * b - b * 14, ecx = a * b - b * 14, ebx = b * 14
            mov ecx, a;     ecx = a, eax = a * b - b * 14, ebx = b * 14
            cdq;            ecx = a, eax = a * b - b * 14, ebx = b * 14
            idiv ecx;       eax = (a * b - b * 14) / a
            jmp save_res;   eax = (a * b - b * 14) / a
            greater :
        add ebx, 5;         ebx = b + 5, ecx = a
            jo of;          ebx = b + 5, ecx = a
            jz dividing_zero; ebx = b + 5, ecx = a
            mov eax, ecx;       eax = a, ebx = b + 5, ecx = a
            cdq;                eax = a, ebx = b + 5
            idiv ebx;       eax = a / (b + 5), ebx = b + 5, ecx = a
            sub eax, 10;    eax = a / (b + 5) - 10, ebx = b + 5
            jo of;          eax = a / (b + 5) - 10, ebx = b + 5
            jmp save_res
            dividing_zero :
        mov div_zero, 1
            jmp exit_asm
            save_res :
        mov x, eax;         x = eax
            jmp exit_asm
            of :
        mov overflow, 1
            jmp exit_asm
            exit_asm :
    }
    output(x, div_zero, overflow);
}


int main()
{
    int a;
    int b;
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
