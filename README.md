# Epameny

## A ridiculous ANSI menu in Bash

## Help

(This README document may be out of date - best check the script itself)

```
epameny v0.9.3: A ridiculous ANSI menu

Usage:
  epameny <title> <default item index> <item label> <item value> [...]

The interactive menu is printed to standard error, and the selection
is printed to standard output in the form '<item index> <item value>'
where the former is, like the default item index, a 0-indexed integer
counting from the first item supplied, and the latter is the
corresponding item's value, with no additional quoting or escaping.
A negative default index can be used to select items in reverse order.

Keys:
  ISO up / down or 'l' / 'j' moves the selection up / down
  RETURN / ENTER confirms the item selection and exits
  'q' exits immediately (as does choosing a '::quit::'-value)

Exit states:
  On immediate exit     : Exit code 2, prints nothing to stdout
  On interrupt (^C etc) : Exit code 1, prints nothing to stdout
  On item confirmation  : Exit code 0, prints <index> <value> to stdout
                          Except when the selected value is '::quit::'

Special labels & values:
  Setting a label or a value to '::' copies its obverse property;
  Confirmation on a '::quit::' value is equivalent to pressing 'q'

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
