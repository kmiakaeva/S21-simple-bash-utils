# School 21. Simple Bash Utils

Development of Bash text utilities: cat, grep.

### s21_cat

TEMPLATE: `cat [OPTION] [FILE]`

| No. | Option                                                      | Description                                  | Status |
| --- | ----------------------------------------------------------- | -------------------------------------------- | ------ |
| 1   | -b (GNU: --number-nonblank)                                 | numbers only non-empty lines                 | ☑️    |
| 2   | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $ | ☑️     |
| 3   | -n (GNU: --number)                                          | number all output lines                      | ☑️     |
| 4   | -s (GNU: --squeeze-blank)                                   | squeeze multiple adjacent blank lines        | ☑️     |
| 5   | -t implies -v (GNU: -T the same, but without implying -v)      | but also display tabs as ^I                  | ☑️     |

### s21_grep

TEMPLATE: `grep [OPTION] [TEMPLATE] [FILE]`

| No. | Option  | Description                                                   | Status |
| --- | ------- | ------------------------------------------------------------- | ------ |
| 1   | -e      | pattern                                                       | ☑️     |
| 2   | -i      | ignore uppercase vs. lowercase                                | ☑️     |
| 3   | -v      | invert match                                                  | ☑️     |
| 4   | -c      | output count of matching lines only.                          | ☑️     |
| 5   | -l      | output matching files only                                    | ☑️     |
| 6   | -n      | precede each matching line with a line number                 | ☑️     |
| 7   | -h      | output matching lines without preceding them by file names    | ☑️     |
| 8   | -s      | suppress error messages about nonexistent or unreadable files | ☑️     |
| 9   | -f file | take regexes from a file                                      | ☑️     |
| 10  | -o      | output the matched parts of a matching line                   | ☑️     |

## Run Locally

1. Clone the project

```bash
  git clone https://github.com/kmiakaeva/s21-simple-bash-utils
```

2. Go to the project directory

```bash
  cd s21-simple-bash-utils
```

3. Go to the cat or grep folder

```bash
  cd src/cat
```
```bash
  cd src/grep
```

4. Run make for build

```bash
  make
```

5. Run test

```bash
  make run
```