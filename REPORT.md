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
