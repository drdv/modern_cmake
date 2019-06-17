find_package(LATEX)
if(LATEX_FOUND)
  include(UseLATEX)

  set(notes_filename "note")
  add_latex_document(${notes_filename}.tex BIBFILES biblio.bib)

  add_custom_target(open
    COMMAND open ${notes_filename}.pdf
    COMMENT "Open latex document.")

  set_target_properties(open auxclean html pdf ps
    note note_pdf note_safepdf _note dvi safepdf
    note_html note_ps note_auxclean note_dvi
    PROPERTIES FOLDER internal)

else()
  message("--> [SKIP] latex note")
endif(LATEX_FOUND)
