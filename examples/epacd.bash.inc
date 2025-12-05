#!/usr/bin/env bash
# This is an example for epameny.
# A `cd` wrapper menu in the form of a bash function.
# Source it in your shell (e.g '. cd_menu_function; cd_menu') to try it.

epacd() {
    local header=('OK' '::quit::' '⬏ ../' '../')
	local dir data
    clear
    while true; do
        local list=()
        mapfile -t dirlist < <(compgen -G '*/')
        for dir in "${dirlist[@]}"; do list+=("$dir" '::'); done
        echo -e "\033[H\033[4m$PWD\033[0m\033[J"
        data=($(meny_pick=1 epameny "${header[@]}" "${list[@]}" )) || return
        filename="${data[@]:1}"
        cd "$filename"
    done
}
