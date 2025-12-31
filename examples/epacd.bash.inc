# A `cd` wrapper menu in the form of a bash function.
# Source it in your shell (e.g '. epacd.bash.inc; epacd') to try it.
# This is an example for epameny.

epacd() {
    local header=('OK' '::quit::' '⬏ ../' '../')
	local dir data
    export meny_aheight=-1 meny_pick=1
    while true; do
        local list=()
        compgen -V dirlist -G '*/' # Hidden dirs excluded..
        for dir in "${dirlist[@]}"; do list+=("$dir" '::'); done
        echo -e "\033[H\033[4m$PWD\033[0m\033[J"
        data=($(epameny "${header[@]}" "${list[@]}" )) || return
        filename="${data[@]:1}"
        cd "$filename"
    done
}
