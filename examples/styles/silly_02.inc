export meny_sel_prefix="⚪\033[4m" # adds 1 ('⚪' = 1 glyph) to our width
export meny_std_prefix="  "        # adds 2 ('  ' = 2 glyphs).

# Amend epameny's width by the longest of the two.
# This prevents printing past the terminal's width:

export meny_amend_width=-2
