include(UseLATEX)

set(NOTES_FILENAME "note")
add_latex_document(${NOTES_FILENAME}.tex BIBFILES biblio.bib)

add_custom_target(open
  COMMAND open ${NOTES_FILENAME}.pdf
  COMMENT "Open latex document.")
