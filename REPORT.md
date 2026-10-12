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
