Trap routines in the LC-3 are basically built-in helper functions that handle common tasks like getting input from the keyboard or printing text to the screen. You can think of them as the LC-3’s version of operating system functions or system calls. Instead of writing out the same code every time you need to do one of these things, you just use a short instruction (called a “trap”) that jumps to a routine that already knows how to do it.

Each trap routine has its own unique code (called a trap code), and when you call it using the TRAP instruction, the program counter (PC) jumps to the location in memory where that routine lives. When the routine finishes, the program returns to where it left off and continues running. In the LC-3 simulator, these routines are usually written in assembly, but in the virtual machine we write them in C so they can easily use the computer’s own I/O functions.

Here’s what each trap routine does:

TRAP_GETC (0x20)
This reads a single character from the keyboard. It doesn’t show what you typed on the screen (it’s not echoed). The character is stored in register R0.

TRAP_OUT (0x21)
This takes the character stored in register R0 and prints it to the screen. It’s the simplest output function—just one character.

TRAP_PUTS (0x22)
This prints a string of characters to the screen. The address of the first character in the string must be in R0 before calling the trap. Each character is stored in a separate memory location, and the string ends when a memory cell contains 0 (similar to how C strings end with ‘\0’). The routine goes through the string one character at a time and prints each to the screen.

TRAP_IN (0x23)
This asks the user to enter a character. It shows a prompt on the screen, waits for the user to type something, and then both echoes the character and stores it in R0.

TRAP_PUTSP (0x24)
This is another string output routine, but the string is stored in a slightly different way: two characters are packed into one 16-bit memory word (one in each byte). The routine unpacks each character before printing them. It’s a bit more efficient in terms of memory.

TRAP_HALT (0x25)
This stops the program. It prints “HALT” to the screen and then ends execution.

In short, trap routines are like shortcuts for basic input and output actions. They make LC-3 programs cleaner and easier to write because you don’t have to handle the low-level details yourself.