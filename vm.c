/* Memory Storage */

#define MEMORY_MAX ( 1 << 16) /*  creates a constant value (65536) that can be used anywhere in the file. */
uint16_t memory_MAX;  /* 65536 locations, defines a global array variable called memory that has 65536 slots.*/

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




