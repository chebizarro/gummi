// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)

#ifndef GUMMI_PREFS_H
#define GUMMI_PREFS_H

#include <gtk/gtk.h>
#include "gummi-window.h"


#define GUMMI_PREFS_TYPE (gummi_prefs_get_type ())
G_DECLARE_FINAL_TYPE (GummiPrefs, gummi_prefs, GUMMI, PREFS, GtkDialog)


GummiPrefs        *gummi_prefs_new(GummiAppWindow *win);


#endif //GUMMI_PREFS_H
