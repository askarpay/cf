# bf in c++ (UC CS1021 project)

## base goal: create a stack machine as defined by the bf standard, while only referencing the spec.

```
>   Increment the data pointer (to point to the next cell to the right).
<   Decrement the data pointer (to point to the next cell to the left).
+ 	Increment (increase by one) the byte at the data pointer.
- 	Decrement (decrease by one) the byte at the data pointer.
. 	Output the byte at the data pointer.
, 	Accept one byte of input, storing its value in the byte at the data pointer.
[ 	If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
] 	If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command. 
```

## BUILDING

replace clang with your c++ compiler of choice if so desired

`clang cf.cpp -o cf`

## USAGE:

`./cf path/to/program.bf`

the examples/ folder has a few sample programs to test the interpreter out

*NOTE: no programs in the examples folder are mine. all credit is given within each file*
