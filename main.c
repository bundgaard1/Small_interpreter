#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

#include "int3.h"

#define REGISTERS 10
#define RAM 1000

Int3* make_ram() {
  Int3* new_ram = (Int3*)malloc(sizeof(Int3) * RAM);
  for (int i = 0; i < RAM; i++) {
    new_ram[i] = int_to_int3(0);
  }
  return new_ram;
}

Int3* make_registers() {
  Int3* new_register = (Int3*)malloc(sizeof(Int3) * REGISTERS);
  for (int i = 0; i < REGISTERS; i++) {
    new_register[i].n1 = 0;
    new_register[i].n2 = 0;
    new_register[i].n3 = 0;
  }
  new_register[999].n1 = 1;
  return new_register;
}

void scan_instructions(Int3* p) {
  int n;
  scanf("%d \n", &n);

  int curr;
  for (int i = 0; i < n; i++) {
    scanf("%d", &curr);
    p[i].n1 = curr / 100;
    p[i].n2 = curr / 10 % 10;
    p[i].n3 = curr % 100 % 10;
  }

  return;
}

void print_ram(Int3* p) {
  for (int i = 0; i < 15; i++) {
    printf("RAM %2d: %d%d%d\n", i, p[i].n1, p[i].n2, p[i].n3);
  }
}

void print_registers(Int3* p) {
  for (int i = 0; i < REGISTERS; i++) {
    printf("Register %d: %d%d%d\n", i, p[i].n1, p[i].n2, p[i].n3);
  }
}

void run_instruction(Int3 instruction, Int3* p_registers, Int3* p_ram,
                     int* p_curr) {
  int d, n, s, a, new_value;
  // printf("%d%d%d\n", instruction.n1, instruction.n2, instruction.n3);
  switch (instruction.n1) {
    // halt
    case 1:
      if (instruction.n2 == 0 && instruction.n3 == 0) {
        *p_curr = -1;
        return;
      }
      break;
    // set register d to n
    case 2:
      d = instruction.n2;
      n = instruction.n3;
      p_registers[d].n3 = n;
      break;
    // add n to register d
    case 3:
      d = instruction.n2;
      n = instruction.n3;
      new_value = (int3_to_int(p_registers[d]) + n) % 1000;
      p_registers[d] = int_to_int3(new_value);
      break;
    // multiply register d by n
    case 4:
      d = instruction.n2;
      n = instruction.n3;
      new_value = (int3_to_int(p_registers[d]) * n) % 1000;
      p_registers[d] = int_to_int3(new_value);
      break;
    // set register d to the value of register s
    case 5:
      d = instruction.n2;
      s = instruction.n3;
      p_registers[d] = p_registers[s];
      break;
    // add the value of register s to register d
    case 6:
      d = instruction.n2;
      s = instruction.n3;
      new_value =
          (int3_to_int(p_registers[d]) + int3_to_int(p_registers[s])) % 1000;
      p_registers[d] = int_to_int3(new_value);
      break;
      // multiply register d by the value of register s
    case 7:
      d = instruction.n2;
      s = instruction.n3;
      new_value =
          (int3_to_int(p_registers[d]) * int3_to_int(p_registers[s])) % 1000;
      p_registers[d] = int_to_int3(new_value);
      break;
    // set register d to the value in RAM whose address is in register a
    case 8:
      d = instruction.n2;
      a = instruction.n3;
      p_registers[d] = p_ram[int3_to_int(p_registers[a])];
      break;
    // set the value in RAM whose address is in register a to that of register s
    case 9:
      s = instruction.n2;
      a = instruction.n3;
      p_ram[int3_to_int(p_registers[a])] = p_registers[s];

      break;
    // goto the location in register d unless register s contains 0
    case 0:
      d = instruction.n2;
      s = instruction.n3;
      if (int3_to_int(p_registers[s]) != 0) {
        *p_curr = int3_to_int(p_registers[d]);
        return;
      }
      break;

    default:
      break;
  }

  *p_curr += 1;
  return;
}

void run_program(Int3* p_registers, Int3* p_ram) {
  int curr = 0;
  int n = 0;
  while (curr != -1) {
    run_instruction(p_ram[curr], p_registers, p_ram, &curr);
    n++;
  }
  printf("Instructions run: %d\n", n);

  return;
}

int main() {
  Int3* ram = make_ram();
  Int3* registers = make_registers();

  scan_instructions(ram);

  run_program(registers, ram);

  print_ram(ram);
  print_registers(registers);

  return 0;
}
