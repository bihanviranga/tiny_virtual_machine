# Virtual Machine

A stack based virtual machine.

## Registers
General purpose registers: A, B, C, D, E, F

Special purpose registers: IP (instruction pointer), SP (stack pointer)

## Instructions
- PSH: Push to stack
- ADD: Add the two numbers on top of the stack
- POP: Pop the value from the top of the stack
- SET: Set a register to a value
- HLT: Halt execution

## Debugging
Using `#define PRINT_POPPED` every popped value will be printed to stdout.
