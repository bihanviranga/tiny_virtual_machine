#include <stdbool.h>
#include <stdio.h>

// Prints out each value that is popped off the stack
#define PRINT_POPPED
// Prints out the register and the value it is set to
#define PRINT_SET
// Dumps the current registry values when HLT is encountered
#define DUMP_REGISTERS_ON_HALT

// Instructions
typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  HLT,
  JMP
} InstructionSet;

// Registers
typedef enum {
  A, B, C, D, E, F,   // General purpose registers
  IP, SP,             // Instruction pointer and Stack pointer
  NUM_OF_REGISTERS
} Registers;

int registers[NUM_OF_REGISTERS];

// Forward declarations
int fetch();
void eval(int instr);
void dump_registers();

// Program to execute.
// (hard coded for now)
const int program[] = {
  SET, 0,  0,
  SET, 1, 10,
  JMP, 6,
  SET, 2, 20,
  SET, 3, 30,
  SET, 4, 40,
  SET, 5, 50,
  HLT
};

// Whether the VM is running
bool running = true;
// Stack. Size is hard coded for now.
int stack[256];

int main() {
  // Instruction pointer
  registers[IP] = 0;
  // Stack pointer. -1 means uninitialized.
  registers[SP] = -1;

  while (running) {
    eval(fetch());
    (registers[IP])++;
  }

  return 0;
}

// Evalutes the given instruction
void eval(int instr) {
  switch (instr) {
    case HLT: {
      running = false;
#ifdef DUMP_REGISTERS_ON_HALT
      dump_registers();
#endif
      break;
    }
    case PSH: {
      (registers[SP])++;
      stack[registers[SP]] = program[++(registers[IP])];
      break;
    }
    case POP: {
      int popped = stack[(registers[SP])--];
#ifdef PRINT_POPPED
      printf("[POP] %d\n", popped);
#endif
      break;
    }
    case SET: {
      // IP contains the value SET
      // IP+1 contains the value of the register to SET
      // IP+2 contains the value to set in the register
      int reg = program[++(registers[IP])];
      int val = program[++(registers[IP])];
      registers[reg] = val;
#ifdef PRINT_SET
      printf("[SET] Reg: %d Val: %d\n", reg, val);
#endif
      break;
    }
    case ADD: {
      int val_1 = stack[(registers[SP])--];
      int val_2 = stack[(registers[SP])--];
      int result = val_1 + val_2;
      (registers[SP])++;
      stack[(registers[SP])] = result;
      break;
    }
    case JMP: {
      int arg = program[IP + 1];
      // +1 here is to account for the arg
      registers[IP] = registers[IP] + arg + 1;
    }
  }
}

// Returns the instruction at IP
int fetch() {
  // printf("[FETCH] Fetching %d\n", registers[IP]);
  return program[(registers[IP])];
}

// Utility function to dump register values
void dump_registers() {
  printf("[REG] === Registry dump ===\n");
  for (int i = 0; i <= 5; i++) {
    printf("[REG] %d Val: %d\n", i, registers[i]);
  }
  printf("[REG] === End registry dump ===\n");
}
