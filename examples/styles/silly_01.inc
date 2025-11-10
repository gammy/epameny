lextra="⇨" rextra="⇦"
(( meny_width = ${COLUMNS:-80}-(${#lextra}+${#rextra}) ))
export meny_sel_prefix="${lextra}\033[34;1m"
export meny_sel_suffix="\033[0m${rextra}"
export meny_std_prefix="\033[90;1m "
export meny_width
export LINES

