# pBuffer

This program is a contact list manager written in C that intentionally uses a single dynamic memory block (`pBuffer`) to store:

- control variables (selected menu option, number of people, buffer size, flags)
- temporary input text
- all contact records (name, age, e-mail)

## Rules

- **No variables can be declared in the entire program—only pointers are allowed.** All program data must be stored inside `pBuffer`.
    - Not even as function parameters. Only pointers that reference inside `pBuffer`.
        - Example: `int *ptr = (int *)pBuffer;`
        - Not allowed: `int c; char a; int v[10];  void function(int param)`
- **All strings stored in `pBuffer` must use only the space required.** Only the input buffer for reading with `scanf` can be a fixed size.
- **Do not use `struct` anywhere in the program.**

## How it works

At startup, it allocates 500 bytes:

```c
void *pBuffer = malloc(500);
```

Then it places control data at fixed offsets inside this block:

- `op` (`int`): selected menu option
- `i` (`int`): number of stored people
- `currentSize` (`int`): total allocated bytes
- `flag` (`char`): helper flag for search/remove
- `stringScan` (`char*`): temporary input area
- `stringStore` (`char*`): write cursor for persistent records (starts at byte 250)

The first half of the buffer is used for control + temporary input, and records are appended from byte 250 onward.

## Record format in memory

Each person is stored sequentially as:

1. `name` as null-terminated string
2. `age` as `int`
3. `email` as null-terminated string

So records are variable-length due to strings.

## Menu options

1. **Add person**  
   Reads name, age, and e-mail. If free space is low, it grows the buffer by 500 bytes with `realloc` and fixes all internal pointers.

2. **Remove person**  
   Searches by name. If found, removes the full record by shifting the remaining bytes left using `memmove`.

3. **Search person**  
   Scans records by name and prints name, age, and e-mail when found.

4. **List**  
   Iterates through all stored records and prints each contact.

5. **Exit**  
   Frees memory and terminates the program.

## Notes

- Input for strings is limited by `scanf(" %99[^\n]", ...)`.
- This is an exercise in manual memory layout using pointer arithmetic.
