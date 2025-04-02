#include <iostream>

int sz_input()
{
  int res;
  while (!(std::cin >> res) || std::cin.peek() != '\n' || res <= 0)
  {
    std::cin.clear();
    while (std::cin.get() != '\n');
    std::cout << "You haven't enetered a valid value\n";
    std::cout << "Enter an integer positive number\n";
  }
  return res;
}

int int_input()
{
  int res;
  while (!(std::cin >> res) || std::cin.peek() != '\n')
  {
    std::cin.clear();
    while (std::cin.get() != '\n');
    std::cout << "You haven't enetered a valid value\n";
    std::cout << "Enter an integer number\n";
  }
  return res;
}

void array_input(int* const arr, const int size)
{
  for (size_t i = 0; i < size; ++i)
  {
    std::cout << "Element " << i <<":\n";
    arr[i] = int_input();
    std::cout << std::endl;
  }
}

void output_res(int x)
{
  std::cout << "CPP result:\n";
  std::cout << x << std::endl;
}

void output_res(int res, bool overflow)
{
  std::cout << "ASM result:\n";
  if (overflow)
    std::cout << "ASM Error: overflow\n";
  std::cout << res << std::endl;
}

void asm_f(int* const arr,  const int sz)
{
  int res = 0;
  bool over = false;
  __asm
  {
    xor esi, esi; esi = 0
    push 0; stack head = 0
    mov ebx, arr; ebx = arr
    mov ecx, sz; ecx = sz
    begin_loop : ; начало цикла
      mov edx, [ebx + esi * 4]; edx = текущий элемент массива
      test edx, edx; positive
      js end_loop; -1->end_loop
      mov eax, edx; eax = edx
      mul eax; eax = eax * eax
      jo of_flag
      pop ebx; get head steak
      add eax, ebx; eax = eax + ebx
      jo of_flag
      push eax; put to stack
      mov ebx, arr; ebx = arr
    end_loop:
      inc esi; esi = esi + 1
      loop begin_loop; jump to begin_loop
      pop eax; get res
      mov res, eax; move res
    jmp ex
    of_flag:
      pop eax; take eax
      mov over, 1; over = 1
    ex:
  }
  output_res(res, over);
}

void cpp_f(int* const arr, const int sz)
{
  int res = 0;
  for (int i = 0; i < sz; ++i)
  {
    res += *(arr + i) > 0 ? std::pow(*(arr + i), 2) : 0;
  }
  output_res(res);
}

int main()
{
  while (true)
  {
    std::cout << "The program finds the sum of the squares of all the positive elements of the array\n";
    std::cout << "Enter the size of the array\n";
    int size = sz_input();
    int* arr = new int[size];
    array_input(arr, size);
    asm_f(arr, size);
    cpp_f(arr, size);
    delete[] arr;
  }
}