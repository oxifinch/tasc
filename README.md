# TASC - Task Scanner
---
A simple command line utility which scans source files for comments labeled
"**TODO**" and creates a `todo.md` file with checkboxes for each task it finds.

## Usage
Run `tasc` on any number of files, for example `tasc src/*`. The resulting `todo.md`
file should contain task items with the filename and line number attached, something
like this:
```md
- [ ] src/main.c:32 Move these functions to their own separate files
- [ ] src/parsing.c:78 This works, but the implementation is a bit janky
- [ ] src/parsing.c:93 Handle errors here, don't assume input is valid
```

---

## TO DO
Essential features:
- [ ] Read file(s) from command line
- [ ] Scan each file and find TODO lines
- [ ] Parse each line and return a formatted string
- [ ] Append formatted string to `todo.md` file

Nice extra features:
- [ ] Filter out comment correctly depending on language/comment style
- [ ] Handle multi-line TODO items
- [ ] Keep old/don't overwrite finished tasks in `todo.md` when running Tasc again
