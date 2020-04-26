cmake_minimum_required(VERSION 3.10)
project(gummi C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK REQUIRED gtk+-3.0)
pkg_check_modules (GTK_SOURCEVIEW REQUIRED gtksourceview-3.0)
pkg_check_modules (POPPLER REQUIRED poppler-glib)
pkg_check_modules (SYNCTEX REQUIRED synctex<2.00)
pkg_check_modules (GTK_SPELL REQUIRED gtkspell3-3.0)

include_directories (
        ${GTK_INCLUDE_DIRS}
        ${GTK_SOURCEVIEW_INCLUDE_DIRS}
        ${POPPLER_INCLUDE_DIRS}
        ${GTK_SPELL_INCLUDE_DIRS}
        ${SYNCTEX_INCLUDE_DIRS})

set (GUMMI_LIBRARIES
        ${GTK_LIBRARIES}
        ${GTK_SOURCEVIEW_LIBRARIES}
        ${POPPLER_LIBRARIES}
        ${GTK_SPELL_LIBRARIES}
        ${SYNCTEX_LIBRARIES})


link_directories (${GTK_LIBRARY_DIRS})
link_directories (${GTK_SOURCEVIEW_LIBRARY_DIRS})

include_directories(.)
include_directories(src)
include_directories(src/compile)
include_directories(src/gui)

add_definitions(
        -DGUMMI_LIBS="/${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}"
        -DGUMMI_DATA="/${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}"
        -DGUMMI_LOCALES="/${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}"
        -DUSE_SYNCTEX1
)

add_executable(gummi
        src/compile/latexmk.c
        src/compile/latexmk.h
        src/compile/rubber.c
        src/compile/rubber.h
        src/compile/texlive.c
        src/compile/texlive.h
        src/gui/gui-import.c
        src/gui/gui-import.h
        src/gui/gui-infoscreen.c
        src/gui/gui-infoscreen.h
        src/gui/gui-main.c
        src/gui/gui-main.h
        src/gui/gui-menu.c
        src/gui/gui-menu.h
        src/gui/gui-prefs.c
        src/gui/gui-prefs.h
        src/gui/gui-preview.c
        src/gui/gui-preview.h
        src/gui/gui-project.c
        src/gui/gui-project.h
        src/gui/gui-search.c
        src/gui/gui-search.h
        src/gui/gui-snippets.c
        src/gui/gui-snippets.h
        src/gui/gui-tabmanager.c
        src/gui/gui-tabmanager.h
        src/biblio.c
        src/biblio.h
        src/configfile.c
        src/configfile.h
        src/constants.h
        src/editor.c
        src/editor.h
        src/environment.c
        src/environment.h
        src/external.c
        src/external.h
        src/importer.c
        src/importer.h
        src/iofunctions.c
        src/iofunctions.h
        src/latex.c
        src/latex.h
        src/main.c
        src/motion.c
        src/motion.h
        # src/plugin-manager.c
        # src/plugin-manager.h
        src/project.c
        src/project.h
        src/signals.c
        src/signals.h
        src/snippets.c
        src/snippets.h
        src/tabmanager.c
        src/tabmanager.h
        src/template.c
        src/template.h
        src/utils.c
        src/utils.h
        config.h)

target_link_libraries (gummi ${GUMMI_LIBRARIES})
