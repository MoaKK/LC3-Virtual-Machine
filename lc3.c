#include <stdint.h>

/* Memory Storage */

#define MEMORY_MAX (1 << 16) /*  creates a constant value (65536) that can be used anywhere in the file. */
uint16_t memory[MEMORY_MAX]; /* 65536 locations, defines a global array variable called memory that has 65536 slots.*/

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
	OP_ADD,		 /* add  */
	OP_LD,		 /* load */
	OP_ST,		 /* store */
	OP_JSR,		 /* jump register */
	OP_AND,		 /* bitwise and */
	OP_LDR,		 /* load register */
	OP_STR,		 /* store register */
	OP_RTI,		 /* unused */
	OP_NOT,		 /* bitwise not */
	OP_LDI,		 /* load indirect */
	OP_STI,		 /* store indirect */
	OP_JMP,		 /* jump */
	OP_RES,		 /* reserved (unused) */
	OP_LEA,		 /* load effective address */
	OP_TRAP		 /* execute trap */
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

/* Main Loop */

/* Main function is the heart of a LC-3 virtual machine.

It runs a continuous loop that acts like a CPU: fetching, decoding, and executing instructions from memory — just like real hardware does.

Here’s what happens step by step:
	1.	Setup
	•	Initialize registers and memory.
	•	Set the condition flag to “zero” (FL_ZRO).
	•	Set the program counter (R_PC) to the default start address 0x3000 (where LC-3 programs begin).
	2.	Main loop (the CPU cycle)
The line while (running) is your CPU running forever until a halt instruction stops it. Each loop does one instruction cycle:
a) Fetch
	•	Read the next instruction from memory:
uint16_t instr = mem_read(reg[R_PC]++);
This gets the instruction at the address in R_PC, then increases R_PC to point to the next one.
b) Decode
	•	Figure out which operation it is by checking the top 4 bits:
uint16_t op = instr >> 12;
c) Execute
	•	The switch(op) decides what to do:
	•	If it’s OP_ADD, run the ADD logic.
	•	If it’s OP_AND, run the AND logic.
	•	If it’s OP_BR, run the branch logic, etc.
	•	Each case represents one LC-3 instruction being executed.
	3.	Shutdown
	•	When a HALT trap (TRAP x25) is hit,
	the program sets running = 0 to stop the loop and clean up before exiting.*/

int
main(int argc, const char *argv[])
{
	/* Load Arguments */
	if (argc < 2)
	{
		printf("lc3 [image-file1] ...\n");
		exit(2);
	}

	for (int j = 1; j < argc; ++j)
	{
		if (!read_image(argv[j]))
		{
			printf("failed to load image %s\n", argv[j]);
			exit(1)
		}
	}

	signal(SIGINT, handle_interrupt);
	disable_input_buffering();

	/* Only one condtional flag should be active at any moment, because when one starts
	the program, no calculcations will have been done yet. So the safest default is to assume
	the last result was zero

	When the VM starts, no instruction has run yet, so the condition flags (positive, zero, negative) don’t have a valid value,
	they could contain random bits from memory.

	If we don’t set one, then when the program tries to do something like BRz (branch if zero),
	it might behave unpredictably because the flags aren’t defined.
	*/
	reg[R_COND] = FL_ZRO

			/* 0x3000 is a memory address, written in hexadecimal (base 16).
			It’s just the conventional starting point where LC-3 programs are loaded before they run.

			Here’s what it means:
		•	The LC-3 memory goes from address 0x0000 to 0xFFFF (65,536 locations total).
		•	The operating system or system data would usually occupy the lower addresses.
		•	User programs are loaded starting at 0x3000 by default.

			So when we write:
			reg[R_PC] = 0x3000;
			we’re telling the CPU:
			“Start fetching and executing instructions from memory location 0x3000.”

			That’s why it’s called the starting position — it’s where your LC-3 program begins its first instruction. */
			enum { PC_START = 0x3000 };
	reg[R_PC] = PC_START;

	int running = 1;
	while (running)
	{
		/*
			•	The CPU looks at the program counter (R_PC) to see where the next instruction is stored in memory.
			•	mem_read(...) fetches that instruction from memory.
			•	The ++ after reg[R_PC] means “after reading, move PC to the next address,” so it points to the next instruction for the next cycle.
		*/
		uint16_t instr = mem_read(reg[R_PC]++);
		/*
			•	Every LC-3 instruction is 16 bits.
			•	The first 4 bits (the leftmost ones) represent the opcode, e.g. the instruction type (ADD, AND, BR, etc.).
			•	Shifting right by 12 moves those 4 bits into the lowest position so we can easily read them.
		*/
		uint16_t op = instr >> 12;

		switch (op)
		{
		case OP_ADD:
		break;
		case OP_AND:
			break;
		case OP_NOT:
			break;
		case OP_BR:
			break;
		case OP_JMP:
			break;
		case OP_JSR:
			break;
		case OP_LD:
			break;
		case OP_LDI:
			break;
		case OP_LDR:
			break;
		case OP_LEA:
			break;
		case OP_ST:
			break;
		case OP_STI:
			break;
		case OP_STR:
			break;
		case OP_TRAP:
			break;
		case OP_RES:
		case OP_RTI:
		default:
			break;
		}
	}
}

/* Update Flags */
void update_flags(uint16_t r)
{
	if (reg[r] == 0)
	{
		reg[R_COND] = FL_ZRO;
	}
	else if (reg[r] >> 15)
	{
		reg[R_COND] = FL_NEG;
	}
	else
	{
		reg[R_COND] = FL_POS;
	}
}