# LC3-Virtual-Machine
Virtual machine (VM) that can run assembly language programs, such as 2048 or my Rogue.

## Structure


lc3.c - the vm/emulator

docs - more explanations for functions used in lc3.c file

programs - Programs like 2048 and Rogue


## Running the VM

### 1. Clone the repo

#### 2. Compile the VM
Use your C compiler to build the executable:
```bash
gcc lc3-vm.c -o lc3-vm

2. Download a Program

Download a compiled LC-3 program, such as 2048 or Rogue. (2048 and Rogue is already provided in the repo)

3. Run the VM

Run the VM with the .obj file as an argument, for example:

./lc3-vm programs/2048.obj

4. Play 2048

Control the game using the W, A, S, and D keys.
When prompted:

Are you on an ANSI terminal (y/n)? y

You should see the game board appear:

+--------------------------+
|                          |
|                          |
|                          |
|                     2    |
|                          |
|   2                      |
|                          |
|                          |
|                          |
+--------------------------+

Press CTRL + C to exit

````


### Sources
https://www.jmeiners.com/lc3-vm/supplies/lc3-isa.pdf

https://www.jmeiners.com/lc3-vm/
