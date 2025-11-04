# Epameny

## A ridiculous ANSI menu in Bash

## Help

(This README document may be out of date - best check the script itself)

```
epameny v0.9.4: A ridiculous ANSI menu

Usage:
  epameny <title> <default item index> <item label> <item value> [...]

Creates an interactive menu consisting of one or more label/value-pairs.
Once an item is confirmed, the associated item index & value is printed
to standard output for the caller to capture & process.

As index-values start counting from 0, the index of the first item is 0.
A negative default index can be used to select items in reverse order.
Title and default index are mandatory, but can be left empty.

Keys:
  Up / Down, 'l' / 'j'   - Move the selection up or down.
  Return / Enter         - Confirm the item selection.
  'q' / 'Q'              - Exit immediately (see also '::quit::').

Exit states:
  On immediate exit      - Exit code 2, prints nothing to stdout.
  On interrupt (^C etc)  - Exit code 1, prints nothing to stdout.
  On item confirmation   - Exit code 0, prints <index> <value> to stdout,
                           Except when the selected value is '::quit::'.

Special labels & values:
  A label or value set to '::' will copy the other field's content.
  A value set to '::quit::' behaves the same as if 'q' was pressed.

Example:
  res=($(epameny 'Menu' -1 'Foo bar' :: 'Baz' 'Bizzle' Quit ::quit::)) || exit
  index="${res[0]}"   # First parameter is the selected index
  value="${res[@]:1}" # Remaining parameters are the value
  echo "User selected index $index, value '$value'"
```

## Requirements

 * `bash`

## Contact

You can reach me via github: [https://github.com/gammy](https://github.com/gammy)
