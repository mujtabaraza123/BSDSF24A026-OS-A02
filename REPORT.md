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
