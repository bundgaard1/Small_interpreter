# Small interpreter
A small "computer" which has 10 registers and 1000 words of RAM. Both RAM and registers contain a 3 digit number (initialized to "000"). 

Input to the program determine the contents of the first *n* RAM locations.
The program runs the RAM as instructions, which are encoded as follows:

```
  - 100   means halt
  - 2dn   means set register d to n (between 0 and 9)
  - 3dn   means add n to register d
  - 4dn   means multiply register d by n
  - 5ds   means set register d to the value of register s
  - 6ds   means add the value of register s to register d
  - 7ds   means multiply register d by the value of register s
  - 8da   means set register d to the value in RAM whose address is in register a
  - 9sa   means set the value in RAM whose address is in register  register s
  - 0ds   means goto the location in register d unless register s 
```

The program output the total number instructions which where executed.
The state of the RAM and registers can also be printed out.
