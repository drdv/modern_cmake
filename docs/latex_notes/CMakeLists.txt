find_package(LATEX)
if(LATEX_FOUND)
  include(UseLATEX)

  set(notes_filename "note")
  add_latex_document(${notes_filename}.tex BIBFILES biblio.bib)

  add_custom_target(open
    COMMAND open ${notes_filename}.pdf
    COMMENT "Open latex document.")
else()
  message("--> [SKIP] latex note")
endif(LATEX_FOUND)
