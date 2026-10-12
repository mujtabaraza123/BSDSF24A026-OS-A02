## Feature 2: Long Listing (`-l`)

### Objective
To extend the starter program with a long-listing option similar to Linux `ls -l`.

### Implementation
- Added the `-l` command-line option using `getopt()`.
- Displayed file permissions, link count, owner, group, file size, modification time, and filename.
- Used `lstat()` to retrieve information about symbolic links.
- Added permission formatting for regular files, directories, and symbolic links.
- Used formatted output fields to improve column alignment.
- Preserved the original `do_ls()` function for normal directory listing.

### Testing
- `make` compiled the program successfully without errors.
- `./bin/ls -l` displayed long-format information for the project directory.
- `./bin/ls -l /etc` and `./bin/ls -l /tmp` successfully listed other directories.

### Conclusion
The `-l` option works successfully and displays detailed file information. Further features will be implemented in separate branches as required by the assignment.

### Report Questions — Feature 2

**Q1. What is the crucial difference between `stat()` and `lstat()`? When is `lstat()` more appropriate?**

`stat()` follows a symbolic link and returns information about its target. `lstat()` returns information about the symbolic link itself. For `ls`, `lstat()` is more appropriate when displaying the link's own file type and permissions.

**Q2. How do bitwise operators and predefined macros extract information from `st_mode`?**

The `st_mode` field contains file type and permission bits. `S_ISDIR(mode)` checks whether a file is a directory. The expression `mode & S_IRUSR` checks whether the owner has read permission. Similar macros and bit masks check other file types and permissions.


## Feature 3: Column Display (Down Then Across)

### Q1. Explain the logic of down-then-across display. Why is a simple single loop insufficient?

The program first stores all visible filenames in a dynamically allocated array and finds the longest filename. It calculates the number of columns and rows using the terminal width and filename length. The program then prints filenames using `index = row + col * num_rows`, displaying entries down each column and then across the next column. A simple single loop is insufficient because it cannot arrange filenames into aligned columns in the required down-then-across order.

### Q2. What is the purpose of `ioctl()`? What are the limitations of a fixed 80-column fallback?

The `ioctl()` system call with `TIOCGWINSZ` obtains the current terminal dimensions, including its width. This allows the program to adjust the number of columns to the terminal size. A fixed 80-column fallback may cause poor alignment or wrapping when the actual terminal is narrower or wider than 80 columns.

## Feature 4: Horizontal Column Display (-x)

### Q1. Compare the complexity of down-then-across and horizontal printing.

Down-then-across printing requires more pre-calculation because the program must calculate the number of rows and columns before printing. Horizontal printing processes filenames from left to right and wraps to the next line when the terminal width is reached.

### Q2. How does the program manage the display modes (-l, -x, and default)?

The program uses flags to select the display mode. The `-l` option sets `long_format`, while `-x` sets `horizontal_format`. If `-l` is selected, `do_long_listing()` is called. Otherwise, if `-x` is selected, `do_horizontal_ls()` is called. If neither option is selected, `do_column_ls()` provides the default down-then-across display.


## Feature 5: Alphabetical Sort

### Q1. How is alphabetical sorting implemented?

The program uses the `qsort()` function to sort filenames alphabetically. A comparison function named `compare_names()` compares two filenames using `strcmp()`. The filenames are sorted before they are displayed.

### Q2. How does sorting work with different display modes?

The program sorts filenames in the default column display, horizontal display using `-x`, and long listing using `-l`. Each display function sorts the filenames before printing them, so all three modes show entries in alphabetical order.


### Feature 6: Colorized Output Based on File Type

**Q1. How do ANSI escape codes work to produce color in a standard Linux terminal? Show the specific code sequence for printing text in green.**

**Answer:** ANSI escape codes are special character sequences that control text colors and styles in a Linux terminal. The sequence `\033[0;32m` sets the text color to green, and `\033[0m` resets it to the default color.

Example:
```c
printf("\033[0;32mGreen Text\033[0m\n");
```

**Q2. To color an executable file, you need to check its permission bits. Explain which bits in the `st_mode` field you need to check to determine if a file is executable by the owner, group, or others.**

**Answer:** The `st_mode` field contains permission bits that indicate whether the owner, group, or others can execute a file. The bits are `S_IXUSR` for the owner, `S_IXGRP` for the group, and `S_IXOTH` for others. If any of these bits is set, the file has an execute permission.

Example:
```c
if (mode & (S_IXUSR | S_IXGRP | S_IXOTH))
{
    /* Print filename in green */
}
```
