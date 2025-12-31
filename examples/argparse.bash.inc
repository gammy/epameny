# An option-to-export function for epameny, for anyone who wants it.
# Usage example:
# As an external file:
#    source <this> --pick=-1 --aheight=-4 --trimmark='...'
#    epameny ...
# As copied to a pre-existing script:
#    exports=()
#    epameny_argparse exports "${your_script_options[@]}"
#    export "${exports[@]}"
#    epameny ...

# Convert longopts-style options ("--width=..", "--pickfmt=..") to
# environment variable exports (`meny_width=..`, `meny_pickfmt=..`)
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
unset epameny_export exports # cleanup
