# This is a configuration example for epameny.
# Add a bulletpoint to the beginning a selected label and underline the text.
# Also add a space to the beginning of unselected labels to align them.

sel="⚪" # adds 1 ('⚪' = 1 glyph) to our width
uns="  " # adds 2 ('  ' = 2 glyphs)

# Ajdust width to the longer of the two (-1 or -2 respectively)
(( meny_awidth = (${#sel} > ${#uns} ? ${#sel} : ${#uns}) * -1 ))

export meny_awidth
export meny_pickfmt="${sel}\033[4m::label::" # 1 visible, 6 invisible
export meny_normfmt="${uns}::label::"        # 2 visible
