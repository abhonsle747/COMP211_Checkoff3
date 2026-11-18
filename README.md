# Stack Buffer Overflows - COMP 211 Checkoff 3

My checkoff 3 topic is stack buffer overflows (part of the buffer overflows and
memory vulnerabilities topic).

A stack buffer overflow happens when a program writes more data into a local
buffer than it has room for. The extra bytes spill into nearby stack memory,
potentially changing other variables or overwriting information used to return
from a function. This can make the program crash, behave incorrectly, or let an
attacker take control of its execution.

## What I explored

I picked this topic because we spent a lot of time on the stack and pointers in
class, but I never really thought about what happens when you write past the
end of an array. C just lets you do it, and I wanted to see what that actually
looks like in memory.

The main things I looked at:
- how local variables and the return address are laid out on the stack
- what happens when `strcpy` copies more than the buffer can hold
- what protections the compiler and OS add (stack canaries and ASLR)
- how to write the same code safely

## Most interesting things I found

1. One extra character was enough to become admin. In `01_admin_flag.c`,
   `is_admin` sits right after a 16 byte `name` buffer. Typing 16 A's and a B
   puts the B (66 in ASCII) into `is_admin`, and since anything nonzero is true
   in C, it prints ACCESS GRANTED. Nothing crashed and there was no warning.
2. **The compiler already protects you a little.** On Linux, gcc adds a stack
   canary by default, so the bigger overflow in `02_stack_smash.c` gets caught
   with "stack smashing detected" instead of jumping to a garbage address. On
   my Mac it was even stricter: the overflow got blocked at the `strcpy` itself
   ("trace trap"), even for demo 1.
3. **The defenses don't stop everything.** Canaries and ASLR protect the return
   address, but they do nothing about demo 1, because that overflow only changes
   a variable right next to the buffer. The real fix is not overflowing in the
   first place, like using `snprintf` with the buffer size (`04_fixed.c`).

## How to run

Run these in the course container (`learncli/comp211`) or another Linux machine
with gcc. On a Mac the overflows get blocked, so demo 1 won't work the same way.

```bash
./demo.sh
```

This compiles everything and steps through the demo (press Enter for each step).
You can also run one by hand:

```bash
gcc 01_admin_flag.c -o 01_admin_flag
./01_admin_flag AAAAAAAAAAAAAAAAB
```


## Slides
See `slides.pdf`.

## Resources
- YouTube Video: https://www.youtube.com/watch?v=Rm5taWH3xU0 
- Bryant & O'Hallaron, Computer Systems: A Programmer's Perspective, sections 3.10.3-3.10.4
