[//]: # ({% raw %})

# Cuttle VM
A virtual machine to be used with Cuttle System as a caching engine.

## Reference
C++ deque is being used as a data container. Every operation ends with `\n`. Cuttle VM supports the next types of operations:
* `b` — push back to data deque, accepts type and value, e.g. `b i 123`;
* `f` — push from to data deque, accepts type and value, e.g. `f i 123`;
* `c` — call a function, accepts total number of arguments, number of arguments to deduce type from and function name, e.g. `c 2 0 array`;
* `l` — name the position in the code, e.g. `l foo`;
* `r` — name the position in data container, e.g. `r bar`;
* `g` — go to the position of the code if the last entry in data container is boolean `true`, accepts direction(`<` - backward, `>` - forward) and label name, e.g. `g < while_start_label`;
* `a` — call a function with arguments from data container up to the first position with the given name, accepts position name and function name, e.g. `a array_start array`.

The following data types are supported:
* `i` — integral number data type;
* `s` — string data type, ends with `\n`, to escape it use `\\n`;
* `r` — real number data type;
* `b` — boolean data type, `true` stands for true and everything else stands false.

This is an example of VM's code:

```
b s foo
b i 1
c 2 2 setvar
l start
b s foo
b s foo
c 1 1 getvar
b i 1
c 2 2 +
c 2 2 setvar
b s foo
c 1 1 getvar
b i 2
c 1 1 >
g < start
b s This is a test string
```

## API

```c++
#include "interpreter.hpp"
// ...
std::stringstream input("b r 100.0\nb r 101.0\nb r 19.012383");
std::deque<value_t> arg_stack;
context_t context;
interpret(input, context, arg_stack);
```
For the previous code the next code works:
```c++
value_t val1 = value_t{ { type_id::real },{ context.gc.add(new real_t(100.0)) } };
value_t val2 = value_t{ { type_id::real },{ context.gc.add(new real_t(101.0)) } };
value_t val3 = value_t{ { type_id::real },{ context.gc.add(new real_t(19.012383)) } };
std::deque<value_t> expected = { val1, val2, val3 };
assert(arg_stack == expected);
```

## Building

### Prerequisites
 
- CMake 3.0.2
- Cygwin or MSYS Git if on Windows
- GCC 8.1.0 with C++
- GNU Make if manual process is followed

### Default process

1. Enable CMake support in your IDE (Visual Studio, Visual Studio Code or CLion).
2. Open directory using your IDE.

### Manual process

1. Under the project directory execute:
    * `./scripts/get-deps.sh` if you don't have ssh authorization
    * `./scripts/get-deps.sh dev` if you have ssh authorization
2. Create directory build under the project directory.
3. Under the project directory run 
    1. `cd build`
    2. `cmake ..`
    3. `make`

[//]: # ({% endraw %})
