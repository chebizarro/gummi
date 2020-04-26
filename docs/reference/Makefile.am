## Process this file with automake to produce Makefile.in

# see /gtk-doc/examples/Makefile.am

# We require automake 1.6 at least.
AUTOMAKE_OPTIONS = 1.6

# The name of the module
DOC_MODULE = gummi

# The top-level XML file (SGML in the past).
DOC_MAIN_SGML_FILE = gummi-docs.xml

# The directory containing the source code. Relative to $(srcdir).
DOC_SOURCE_DIR = ../../src

# Extra options to supply to gtkdoc-scan.
# e.g. SCAN_OPTIONS = --deprecated-guards="GTK_DISABLE_DEPRECATED"
SCAN_OPTIONS = --rebuild-types --deprecated-guards="GUMMI_DISABLE_DEPRECATED"

# Extra options to supply to gtkdoc-mkdb.
MKDB_OPTIONS = --xml-mode --output-format=xml

# Used for dependencies. The docs will be rebuilt if any of these change.
HFILE_GLOB = $(top_srcdir)/src/*.h
CFILE_GLOB = $(top_srcdir)/src/*.c

# Header files to ignore when scanning (These are internal to gummi).
IGNORE_HFILES =

# Images to copy into HTML directory.
HTML_IMAGES =

# Extra SGML files that are included by $(DOC_MAIN_SGML_FILE).
content_files =

# CFLAGS and LDFLAGS for compiling gtkdoc-scangobj with your library.
# Only needed if you are using gtkdoc-scangobj to dynamically query widget
# signals and properties.
GTKDOC_CFLAGS =			\
	-I$(top_srcdir)/src	\
	-I$(top_builddir)/src \
	-I$(top_srcdir)		\
	-I$(top_builddir)	\
	$(GUMMI_CFLAGS)

GTKDOC_LIBS =						\
	$(GUMMI_LIBS)

MAINTAINERCLEANFILES =

# This includes the standard gtk-doc make rules, copied by gtkdocize.

