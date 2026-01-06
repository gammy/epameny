# Epameny

## About

Epameny is a terminal-based item-selection menu with Bash as its only dependency.

It treats arguments on the command-line (or from `stdin`) as menu-items and
presents them as a vertical menu on the terminal.
The user selects an item and the corresponding value is returned via `stdout`.

It's a very primitive alternative to `dialog`'s standard list-item mode.

*Epa* is used in Swedish to emphasise that something is cruddy or slow.
*Meny* is simply *menu* in Swedish.

## Features

* Lightweight (all OSS tools are lightweight & efficient, didn't you know?)
* Configurable with environment variables
* Easy to use in scripts
* Easy to modify & customise
* Provides scrolling as needed
* Trims labels as needed

## Requirements

* `Bash` version `4.3` (released in 2014) or later \
  (beware Mac & QOS users, your OS uses Bash 3.2 from 2006!)
* A terminal capable of basic ANSI escape sequences \
  (basically any `xterm` or `VT220`-like terminal)

## Limitations

This list could be endless, but this should give you a rough idea.

* Very limited keyboard input handling
* Only supports simplistic vertical lists
* Can't select more than one item
* Can't navigate more than one item at a time
* Lacks pagination & label completion
* Can't auto-determine terminal dimensions (no termcap/terminfo dependency)
* Can't trim on word-boundaries
* Lacks horizontal scrolling
* Lacks real-time signalling mechanisms
* Lacks SIGWINCH-handling (terminal-resizing)

... to be amended by future successors and / or misplaced vanity.

## Usage

Epameny reads arguments either from the command-line or, if the one and only
command-line argument is `-` (a dash-sign), from `stdin`.

The only difference is that when reading from stdin, newline is used as an
argument separator rather than a space.

The following descriptions demonstrate epamenu's operation using the former
input method (command-line arguments).

### Normal mode

In normal mode, items consist of label-value pairs:

```
epameny 'label 1' 'value 1' 'label 2' 'value 2' ...
```

Epameny expects arguments to consist of labels and values ("item pairs"), where
labels are the portion of an item that is presented, and values are the portion
returned upon the user accepting a selection.

```
$ foo=$(epameny 'hello world' 'dance with me')
hello world            <-- user pick
$ echo "$foo"
0 dance with me
```

### Simple mode

In simple mode, things are much the same, except that only labels exist:

```
meny_simple=1
epameny 'label 1' 'label 2' ...
```

As such, epameny expects command-line argument to consist of nothing but labels:

```
$ export meny_simple=1
$ foo=$(epameny 'hello world' 'dance with me')
hello world            <-- user pick
dance with me
$ echo "$foo"
0 hello world
```

## Controls

Controlling epameny, once invoked, is simple:

| Keys               | Action                      |
|:------------------ |:--------------------------- |
| `↑`, `A` or `l`    | Move / scroll up one item   |
| `↓`, `B` or `j`    | Move / scroll down one item |
| `q` or `Q`         | Exit without a result       |
| `Enter`            | Exit with selection         |

Epameny has no mouse support.

## Parsing output

Epameny prints data to be parsed to the standard ouput descriptor (`stdout`),
with the menu itself being printed to the standard error descriptor (`stderr`).
Thus, as the examples above show, the selected value is easily captured.

The output format is simple: The output begins with the selected item's index
(0 being the first item, 1 being the second and so on) followed by a single
space (` `) as a delimiter, and finally the the label's value
(or if `meny_simple=1`, the label).

Epameny doesn't quote the output value.

```
# Capture the selection in an array and splice its elements:
$ data=($(epameny 'Option One' '123' 'Option Two' '1 2 3'))
$ index=${data[0]}
$ value=${data[@]:1}

# Capture result in a string, splicing the index and data:
$ data=$(epameny 'Option One' '123' 'Option Two' '1 2 3')
$ index=${data/ *}
$ value=${data:$((${#index}+1))}"
$ # value=$(echo -n "$data" | cut -d ' ' -f2-)

```

## Exit states

Epameny will only return a zero exit code if the user has made a selection.
If the user cancels the selection (by pressing `q` or by interrupting the process),
a nonzero exit code is returned.

| When                 | Exit code | Output                                   |
|:-------------------- |:---------:|:-----------------------------------------|
| On immediate exit    |     2     | Nothing                                  |
| On interrupt (^C etc)|     1     | Nothing                                  |
| On item confirmation |     0     | `$index $value` unless value = `::quit::`|

A simple way for aborting a process in a script is thus
```
data=$((epameny ...)) || return
```

## Configuration

Epameny versions >= v1.0.0 is configured through environment variables.
Such variables have the prefix `meny_`, and there's quite a lot of them.
Arguably too many for a stupid shellscript.

For those who want it, there is an example CLI option parser in the examples
directory, which maps getopt-long-styled options to environment variables.

## Environment variables

### Default pick (selection)

`meny_pick` can be used to set a different default item (`0` being the default).

Items are zero-indexed: The first item is index 0, the fifth is index 4.
Negative indexes can be used to select items in reversed order.

### Terminal dimensions

Unless `meny_width` and/or `meny_height` have been set, epameny tries to
read the terminal's dimensions via the `LINES` and `COLUMNS` variables. If
neither of those are set, `80` and `25` are used.

`meny_awidth` and `meny_aheight` can be used to adjust the dimensions.
Say you've got your own content occupying two lines (rows) before the menu.
Instead of calculating the dimensions yourself, you can set `meny_aheight=-2`.
These variables are computed within bash, so simple arithmetic is also possible:
`meny_aheight="meny_height / 2"`. `meny_awidth` can also be used to compensate
for invisible characters in labels and/or label-formatting variables.
(see _Appearance_).

### Buffering

Epameny keeps items in an off-screen buffer. The number of items shown on
screen is determined by `meny_height` (see _Terminal dimensions_), other items
becoming visible when the user scrolls up or down. The number of items held
in the full buffer is determined by `meny_limit`, which is set to `1000` by
default. The limit can be disabled with `meny_limit=0`.

Display output is also buffered: rather than print individual parts of the menu,
the entire menu is written to a buffer, which is flushed when needed.

### Trimming

Epameny can't perform word-wrapping, but it can truncate labels at an arbitrary
position with `meny_trimcol`, which specifies the column at which the label
should be trimmed. If `meny_trimcol` is a percentage (i.e `meny_trimcol=50%`),
the position is calculated as a percentage of `meny_width` (the terminal width).

With `meny_trimcol=0`, the beginning (left side) of the label is trimmed,
leaving the end visible. With `meny_trimcol=100%`, the end (right side) is
truncated, leaving the beginning visible. Whether or not the beginning or end
is trimmed depends on this column: left-of-centre trims towards the beginning,
and right-of-centre trims towards the end.

Epameny will - if enough space is available - print a marker (`meny_trimmark`)
at the trim-position For example, `meny_trimcol=100% meny_trimmark=END` will
display `END` on the rightmost side of the terminal when the label's length
exceeds the width of the terminal. The default marker is currently `...`.

### Appearance

Epameny's appearance can be customised a bit.

The `meny_reset` variable defines the ANSI escape sequence printed on start-up
as well as after each label is printed. It defaults to `0m` (reset colors).

The `meny_normfmt` & `meny_pickfmt` variables define the appearance of labels.
The placeholder `::label::` represents the label itself, so that:

```
meny_pickfmt="->::label::<-"
meny_normfmt="  ::label::"
```

Makes the menu appear as this when the 'Bananas' item is picked. ANSI escape
codes will work fine as well, but
```
  Apples
->Bananas<-
  Oranges
```

See also `meny_trimcol` and `meny_trimmark` in _Trimming_.

### Menu-wrapping

Epameny will by default treat the first and last items as endstops. By setting
`meny_wrap=1`, moving past the last item will roll the selection around to the
first one, and vice-versa.

## Label and value placeholders

### "`::label::`"

As detailed in *Appearance*, `meny_normfmt` and `meny_pickfmt` define the
appearance of labels. The placeholder `::label::` is replaced by an actual
label. `Epameny` wants there to be only one such placeholder in each variable.

### "`::`
*Not available in in simple-mode (`meny_simple=1`).*

A label or value set to `::` will copy the other field's content:
`epameny "Good day" ::` is equivalent to `epameny "Good day" "Good day"` and
`epameny :: Computerz` is equivalent to `epameny Computerz Computerz`.

### "`::quit::`"
*Not available in in simple-mode (`meny_simple=1`).*

A value set to `::quit::` behaves the same as if `q` was pressed, resulting in
epameny exiting with exit code `2` with no output on `stdout`.

The following example thus triggers `return` when the user picks `Cancel`:

```
epameny "Foo" :: "Bar" :: "Cancel" ::quit:: || return
```

## Notes

I don't want this to grow much further than it already has: it's been written
as an exercise which I hope might be useful or educational.
The focus has been on zero dependencies (sans bash of course) whilst still being
at least somewhat efficient. If more advanced functionality is needed, it's
probably wise to move to a better menu such as `dialog`, or to rewrite epameny
in a faster and simpler language like C or Python to then extend it.

I quite fancy doing the latter, but time will tell.

### ANSI escape sequences

Epameny uses just a handful of escape sequences to manipulate the terminal:

- `ED` is used for clearing portions of the screen.
- `CUD`, `CUU`, `CHA` & `SGR` are used for movement & default color attributes.
- `DECTCEM` (VT220 cursor enable) is used for showing & hiding the cursor.

## Help

(This README document may be out of date - best check the script itself)

```
epameny v1.0.2: A ridiculous ANSI menu by gammy (code at gammy dot dev)

Usage:
  epameny <label> <value> [<label> <value>] [...]
  meny_simple=1 epameny <label> [label] [...]
  ... | epameny -

Creates an interactive menu consisting of one or more label/value-pairs. Once
an item is confirmed, the associated item index & value is printed to standard
output for the caller to capture & process. The menu itself is printed to
standard error. In simple-mode (meny_simple=1), all items are treated as labels
with values set to '::' (see below). epameny supports vertical scrolling, &
width-trimming of labels.

Indexes count from 0: The first item is index 0, the fifth is index 4.

Keys:
  Up, l, A / Down, j, B  - Move the selection up / down.
  Return, Enter          - Confirm the item selection.
  q, Q                   - Exit immediately. See also '::quit::'.

Exit states:
  On immediate exit      - Exit code 2, prints nothing to stdout.
  On interrupt (^C etc)  - Exit code 1, prints nothing to stdout.
  On item confirmation   - Exit code 0, prints $index $value to stdout,
                           except when the selected value is '::quit::'.
Configurable varibles:
  $meny_pick             - The default picked selection item index.
                           Negative values count backwards from the last item.
  $meny_simple           - Treat all items as labels with values set to '::'.
  $meny_width            - Max. menu width (see also trim options).
  $meny_height           - Max. number of items to display on the screen.
  $meny_limit            - Max. number items to hold in the scroll-buffer.
  $meny_wrap             - 0: Menu stops on its ends. 1: Menu wraps around.
  $meny_reset            - ANSI sequence printed at start & after each item.
  $meny_pickfmt          - Label-format for the selected item.
  $meny_normfmt          - Label-format for all other items.
  $meny_awidth           - Formula or value to add to $meny_width.
  $meny_aheight          - Formula or value to add to $meny_height.
  $meny_trimmark         - Text shown at $meny_trimcol on trimmed labels.
  $meny_trimcol          - Trim long labels on this column position.
                           Represents % of terminal width when ending with '%'.
Default values:
  $meny_pick             - 0    (the first item added is the default item)
  $meny_simple           - 0    (disabled: items must contain a label & value)
  $meny_wrap             - 0    (disabled: menu doesn't wrap around)
  $meny_width            - auto ($COLUMNS if $COLUMNS is set, otherwise 80)
  $meny_height           - auto ($LINES   if $LINES is set, otherwise 25)
  $meny_limit            - 1000 (keep at most 1000 items in total)
  $meny_trimcol          - 100% (labels too long get trimmed at the end)
  $meny_trimmark         - ...  (on trimmed tails, show ... at $meny_trimcol)
  $meny_pickfmt          - '\033[7m::label::\033[7m' (invert colors)
  $meny_reset            - '0m' (default colors)

The length of a label is computed without consideration of ANSI escape codes.
Similarly, meny_pickfmt & meny_normfmt is also not considered. meny_awidth can
be used to adjust the width-calculation if needed. For example if
$meny_normfmt='\e[1m->::label::', meny_awidth should be set to -2 to account
for the arrow whilst ignoring the invisible ANSI code for bolding it.

Placeholders:
  meny_pickfmt & meny_normfmt use '::label::' as a placeholder for labels.
  In normal mode (i.e meny_simple=0), the following applies to labels/values:
  A value set to '::' is substituted by its label & vice-versa.
  A value set to '::quit::' will upon selection act as if 'q' was pressed.

Examples:
  epameny 'A label' 'A value'
  meny_simple=1 epameny 'A label' 'Another label' 'And a third'
  data=($(meny_pick=-1 epameny 'Item A' :: 'Item B' 123 Quit ::quit::)) || exit
  echo "Item index ${data[0]} has value ${data[@]:1}"
  ls | meny_simple=1 epameny -

```

## Contact

You can reach me via github: [https://github.com/gammy](https://github.com/gammy)
