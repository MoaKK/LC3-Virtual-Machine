#include <stdint.h>

/* Memory Storage */

#define MEMORY_MAX ( 1 << 16) /*  creates a constant value (65536) that can be used anywhere in the file. */
uint16_t memory[MEMORY_MAX];  /* 65536 locations, defines a global array variable called memory that has 65536 slots.*/

/* Registers */

enum
{
	R_R0 = 0,
	R_R1,
	R_R2,
	R_R3,
	R_R4,
	R_R5,
	R_R6,
	R_R7,
	R_PC, /* program counter */
	R_COND,
	R_COUNT
};

/* Register storage */
uint16_t reg[R_COUNT];

enum
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
};

/* Contiditional Flags
The R_COND register keeps track of what the result of the last calculation was,
whether it was positive, zero, or negative.

This helps the computer make decisions, like in an if statement.
For example, if you subtract two numbers, the LC-3 sets one of three flags:
	•	P (Positive) if the result > 0
	•	Z (Zero) if the result = 0
	•	N (Negative) if the result < 0

Then, the program can check these flags to decide what to do next.
For instance, whether to jump to another part of the code or continue normally.

The left shift (<<) and right shift (>>) operators move the bits of a number left or right.
	•	Left shift (<<): moves bits to the left and fills with 0s on the right. Each shift left multiplies the number by 2.
	•	Right shift (>>): moves bits to the right. Each shift right divides the number by 2 (for unsigned numbers).

Example:
If you have x = 5, its binary form is 00000101.
	•	x << 1 → 00001010 → 10 (multiplied by 2)
	•	x >> 1 → 00000010 → 2 (divided by 2)

A short is a small integer type in C, usually 16 bits (2 bytes).
	•	Signed short (short or signed short) can store both positive and negative numbers.
	•	Range: −32,768 to 32,767
	•	Unsigned short (unsigned short) can store only positive numbers.
	•	Range: 0 to 65,535
*/

enum
{
	FL_POS = 1 << 0, /* P */
	FL_ZRO = 1 << 1, /* Z */
	FL_NEG = 1 << 2, /* N */
}









