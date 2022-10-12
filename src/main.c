#include <stdbool.h>

// Instructions
typedef enum {
  PSH,
  ADD,
  POP,
  SET,
  HLT
} InstructionSet;

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

// Instruction pointer
int ip = 0;
// Stack pointer. -1 means uninitialized.
int sp = -1;

// Whether the VM is running
bool running = true;
// Stack. Size is hard coded for now.
int stack[256];

int main() {
  while (running) {
    eval(fetch());
    ip++;
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
      sp++;
      stack[sp] = program[++ip];
      break;
    }
  }
}

int fetch() {
  return program[ip];
}
