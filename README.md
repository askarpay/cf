# bf 2 lets go baby

## base goal: create a stack machine as defined by the bf standard, while not referencing any existing code (only the spec)

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

## further task: improve on the language somewhat
this could go two ways. either
- add more useful features
  - add debug character ?
    - print full string so far... maybe hard
- **OR** make it worse..
  - but only if you can make example code still run
    - e.g. hello world

- transpile to c++ instead of just interpret?
- OR create some sort of transpiler to brainfuck. eg take text in and make bf program that prints that text (obfuscator)