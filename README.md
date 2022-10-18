# Virtual Machine

A stack based virtual machine.

## Registers
General purpose registers: A, B, C, D, E, F

Special purpose registers: IP (instruction pointer), SP (stack pointer)

## Instructions
- PSH: Push to stack (`PSH 5`)
- ADD: Add the two numbers on top of the stack
- POP: Pop the value from the top of the stack
- SET: Set a register to a value (`SET 1 5` - set register 1 to value 5)
- HLT: Halt execution
- JMP: Jump n instructions (`JMP 3` - Jump over next 3 instructions)

## To-do
- JE, JNE, JG, JL, JGE, JLE family of instructions.
