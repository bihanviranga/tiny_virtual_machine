#include <stdbool.h>
#include <stdio.h>

// When defined, prints out each value that is popped off the stack
#define PRINT_POPPED

// Instructions
typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  HLT
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

// Program to execute.
// (hard coded for now)
const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
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

void eval(int instr) {
  switch (instr) {
    case HLT: {
      running = false;
      break;
    }
    case PSH: {
      (registers[SP])++;
      stack[registers[SP]] = program[++(registers[IP])];
      // NOTE: should the above RVAL be `program[++(registers[IP])]` ?
      break;
    }
    case POP: {
      int popped = stack[(registers[SP])--];
#ifdef PRINT_POPPED
      printf("[POP] %d\n", popped);
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
  }
}

int fetch() {
  return program[(registers[IP])];
}
