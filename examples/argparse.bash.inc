# An option-to-export function/script for epameny, for anyone who wants it.
# Note that this does not take the '-'-option (introduced in epameny 1.0.2)
# into account.
#
# To use this file as-is:
#    source argparse.bash.inc --pick=-1 --aheight=-4 --trimmark='...'
#    epameny ...
#
# To use the function below in your own script:
#    exports=()
#    epameny_argparse exports "${your_script_options[@]}"
#    export "${exports[@]}"
#    epameny ...


# Convert longopts-style options ("--width=..", "--pickfmt=..") to
# environment variable exports (`meny_width=..`, `meny_pickfmt=..`).
#
# The first param expects a name of an array to which options will be appended.
# Remaining params are expected to be the command-line arguments to parse.
epameny_argparse() {
    local -n export_ptr="$1"; shift
    local arg val valid keywords
    keywords=(simple pick limit wrap width height awidth aheight
              reset normfmt pickfmt trimmark trimcol)
    while (( $# > 0 )); do
        arg="${1/=*}"
        val="${1/*=}"
        shift; valid=0
        for (( i = 0; i < ${#keywords[@]}; i++ )); do
            [[ "$arg" != "--${keywords[$i]/_/-}" ]] && continue
            export_ptr+=("meny_${keywords[$i]}=$val")
            valid=1; break
        done
        (( ! valid )) && echo "'$opt': unknown option" >&2
    done
}

exports=()
epameny_argparse 'exports' "$@"
export "${exports[@]}"
unset epameny_argparse exports # cleanup
