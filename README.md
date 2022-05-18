# hash-table
C implementation of a hash table. Elements of the data structure (keys and values) must be strings.
## Compiling as a Static Library
Run the following commands in the terminal:
```
git clone https://github.com/RJL22/hash-table/edit/main/README.md
cd hash-table/src/
gcc -c hash_table.c prime_generator.c
ar rcs ../build/libhashtable.a hash_table.o prime_generator.o
ranlib ../build/libhashtable.a
```
The library will be stored in the build directory, and it can then be linked to other executables.

