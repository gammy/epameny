# Epameny

## A ridiculous ANSI menu in Bash

## Help

(This README document may be out of date - best check the script itself)

```
epameny v0.9.9-2: A ridiculous ANSI menu by gammy (code at gammy dot dev)

Usage:
  epameny <default item index> <item label> <item value> [...]

Creates an interactive menu consisting of one or more label/value-pairs.
Once an item is confirmed, the associated item index & value is printed
to standard output for the caller to capture & process. The menu itself
is printed to standard error.

Indexes count from 0: The first item is index 0, the fifth is index 4.
A negative default index can be used to select items in reverse order.

Keys:
  Up, l, A / Down, j, B  - Move the selection up / down.
  Return, Enter          - Confirm the item selection.
  q, Q                   - Exit immediately. See also '::quit::'.

Exit states:
  On immediate exit      - Exit code 2, prints nothing to stdout.
  On interrupt (^C etc)  - Exit code 1, prints nothing to stdout.
  On item confirmation   - Exit code 0, prints $index $value to stdout,
                           except when the selected value is '::quit::'.
Environment varibles:
  $meny_width            - Max. menu width. Ellipsises labels from the left.
  $meny_height           - Max. number of items to display on the screen.
  $meny_limit            - Max. number items to hold in the scroll-buffer.
  $meny_wrap             - 0: Menu stops on its ends. 1: Menu wraps around.
  $meny_std_prefix       - Text/ANSI before each non-selected item.
  $meny_std_suffix       - Text/ANSI after each non-selected item.
  $meny_sel_prefix       - Text/ANSI before the selected item.
  $meny_sel_suffix       - Text/ANSI after the selected item.
  $meny_amend_width      - Formula or value to add to $meny_width.

  Defaults:
    $meny_width          - $COLUMNS if present, or 80 if not.
    $meny_height         - $LINES   (-2) if present, or 25 (-2) if not.
    $meny_limit          - 1000     For unlimited items, set it to 0.
    $meny_wrap           - 0        Menu stops at its ends.
    $meny_sel_prefix     - "\e[7m"  ANSI sequence for inverting color.

  As prefixes & suffixes might contain non-printable text (e.g ANSI), their
  string lengths cannot be used when calculating how much to trim the labels.
  As $meny_width + $meny_amend_width = effective width, one solution is to set
  $meny_amend_width to the longest prefix / suffix width used. Given that
  $meny_std_prefix='>' & $meny_sel_suffix='(select)', meny_amend_width should
  be set to -8 (the width of the '(select)'-text) to prevent width-overflow.

Special labels & values:
  A label or value set to '::' will copy the other field's content.
  A value set to '::quit::' behaves the same as if 'q' was pressed.

Example:
  res=($(epameny -1 'Item A' 123 'Item B' :: Quit ::quit::)) || exit
  index="${res[0]}"   # Param 0 : item index
  value="${res[@]:1}" # Param 1+: item value(s)
  echo "Item index $index has value ${value@Q}"
```

## Requirements

 * `bash`

## Contact

You can reach me via github: [https://github.com/gammy](https://github.com/gammy)
