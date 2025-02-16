function _complete()
{
  LATEST="${COMP_WORDS[$COMP_CWORD]}"
  
  STATE="init"
  for ((i=0; i< $COMP_CWORD; i++)) do
    WORD=${COMP_WORDS[$i]}
    WORDS=""
    case "${STATE}" in
      init)
        case "${WORD}" in
          dcw)
            STATE="dcw"
            WORDS="add down list rm up --help"
          ;;
          *)
            STATE="fail"
          ;;
        esac
      ;;
      dcw)
        case "${WORD}" in
          add)
            STATE="add_name"
            WORDS="--create-project"
          ;;
          up)
            STATE="up"
            WORDS="$(dcw list -n)"
          ;;
          rm)
            STATE="rm"
            WORDS=`dcw list -n`
          ;;
          list)
            STATE="list"
            WORDS="--names"
          ;;
          down)
            STATE="down"
            WORDS="--purge"
          ;;
          --help)
            STATE="help"
            WORDS="add down list rm up"
          ;;
          *)
            STATE="fail"
          ;;
        esac
      ;;
      add_name)
        STATE="add_file"
        WORDS=`ls`
      ;;
      up)
        WORDS="--clean"
        STATE="up_name"
      ;;
      *)
      ;;
    esac
  done
  
  COMPREPLY=($(compgen -W "$WORDS" -- $LATEST))
  return 0
}

complete -F _complete dcw
