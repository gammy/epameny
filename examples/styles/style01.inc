# This is a configuration example for epameny.
# Add arrows to the beginning and end of a selected label.
# Also add a space to the beginning of unselected labels to align them.

lextra="⇨" rextra="⇦"

# Ajdust width (-2) to compensate for our extras 
(( meny_awidth = -(${#lextra}+${#rextra}) ))

export meny_awidth
export meny_sel_beg="${lextra}\033[34;1m"
export meny_sel_end="\033[0m${rextra}"
export meny_nsel_beg="\033[90;1m "
export meny_trimcol='50%'
export meny_trimmark=' ~~ '
