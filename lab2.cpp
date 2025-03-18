#include <iostream>


int f_cpp(int a, int b, int c)
{
    int divisible = 2 * b - a + b * c;
    int divider = c / 4 - 1;
    if (divider)
    {
        return divisible / divider;
    }
    std::cout << "CPP: Dividing by 0\n";
    return 0;
}

int input_int()
{
    int res = 0;
    while (!(std::cin >> res) || std::cin.peek() != '\n')
    {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Incorrect input\n";
        std::cout << "Enter the correct num\n";
    }
    return res;
}

int f_asm(int a, int b, int c)
{
    int result = 0;
    bool div_zer = 0, overflow = 0;
    __asm
    {
        mov eax, c;    eax = c
        mov ebx, 4;    ebx = 4, eax = c
        cdq;      eax = c, ebx = 4
        idiv ebx;    eax = c / 4, ebx = 4
        dec eax;    eax = c / 4 - 1, ebx = 4
        jz zero_label;  eax = c / 4 - 1, ebx = 4
        push eax;    eax = c / 4 - 1, ebx = 4
        mov eax, b;    eax = b, ebx = 4
        mov ebx, 2;    eax = b, ebx = 2
        imul ebx;       eax = 2 * b, ebx = 2
        jo of_label;    jump to of_label, eax = 2 * b, ebx = 2
        mov ebx, a;     ebx = a, eax = 2 * b
        sub eax, ebx;   eax = 2 * b - a, ebx = a
        jo of_label;    jump to of_label, eax = eax - ebx, ebx = a
        mov ebx, eax;   ebx = 2 * b - a, eax = 2 * b - a
        mov ecx, c;     ecx = c, ebx = 2 * b - a, eax = 2 * b - a
        mov eax, b;     eax = b, ecx = c, ebx = 2 * b - a
        imul ecx;       eax = c * b, ecx = c, ebx = 2 * b - a
        jo of_label;    jump to of_label
        add eax, ebx;   eax = 2 * b - a + c * b, ecx = c, ebx = 2 * b - a
        jo of_label;    jump to of_label
        pop ebx;        ebx = c / 4 - 1, eax = 2 * b - a + c * b, ecx = c
        cdq;            ebx = c / 4 - 1, eax = 2 * b - a + c * b, ecx = c
        idiv ebx;       eax = (2 * b - a + c * b) / (c / 4 - 1), ebx = c / 4 - 1, ecx = c
        mov result, eax;result = (2 * b - a + c * b) / (c / 4 - 1), eax = (2 * b - a + c * b) / (c / 4 - 1), ebx = c / 4 - 1, ecx = c
        jmp end_label;  end of the asm, eax = (2 * b - a + c * b) / (c / 4 - 1), ebx = c / 4 - 1, ecx = c
        zero_label :
        mov div_zer, 1; div_zer = 1
            jmp end_label;  end of the asm
            of_label :
        mov overflow, 1; overflow = 1
            pop eax; get stack
            jmp end_label; end of the asm
            end_label :
    }
    if (div_zer)
        std::cout << "ASM Error: dividing by 0\n";
    if (overflow)
        std::cout << "ASM Error: overflow\n";
    return result;
}

int main()
{
    int a, b, c;
    while (true)
    {
        std::cout << "Enter a:\n";
        a = input_int();
        std::cout << "Enter b:\n";
        b = input_int();
        std::cout << "Enter c:\n";
        c = input_int();
        std::cout << "The result of CPP\n" << f_cpp(a, b, c) << std::endl;
        std::cout << "The result of ASM\n" << f_asm(a, b, c) << std::endl;
    }
}
