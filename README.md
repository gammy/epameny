# Epameny

## A ridiculous ANSI menu in Bash

## Help

(This README document may be out of date - best check the script itself)

```
epameny v0.9: A ridiculous ANSI menu

Usage:
  epameny <title> <default index> <option text> <option value> [...]

The interactive menu is printed to standard error, and the selection
is printed to standard output in the form '<item index> <item value>'.
The value is not quoted.
Negative default indexes can be used to select items beginning from the
bottom of the list.

Keys:
  ISO up / down or 'l' / 'j' moves the selection up / down
  RETURN / ENTER confirms the item selection and exits
  'q' exits immediately (same as selecting an item with value '::quit::')

Exit states:
  On immediate exit     : Exit code 2, prints nothing to stdout
  On interrupt (^C etc) : Exit code 1, prints nothing to stdout
  On item selection     : Exit code 0, prints <index> <value> to stdout
                          Except when the seleced value is '::quit::'

Two values have special meanings:
  The value of '::' is replaced with the accompanying key
  Selecting a value of '::quit::' is equivalent to pressing 'q'

Example:
  response=($(epameny 'A Menu:' -1 A :: B 'Selected B' Quit ::quit::)) || exit
  index="${response[0]}"   # First parameter is the selected index
  value="${response[@]:1}" # Remaining parameters are the value
  echo "User selected index $index, value '$value'"

```

## Requirements

 * `bash`

## Contact

You can reach me via github: [https://github.com/gammy](https://github.com/gammy)
