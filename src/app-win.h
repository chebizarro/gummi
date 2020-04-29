// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)

#ifndef GUMMI_APP_WIN_H
#define GUMMI_APP_WIN_H

#include <gtk/gtk.h>
#include "app.h"


#define GUMMI_APP_WINDOW_TYPE (gummi_app_window_get_type ())
G_DECLARE_FINAL_TYPE (GummiAppWindow, gummi_app_window, GUMMI, APP_WINDOW, GtkApplicationWindow)


GummiAppWindow       *gummi_app_window_new(GummiApp *app);
void                    gummi_app_window_open(GummiAppWindow *win,
                                              GFile *file);

#endif //GUMMI_APP_WIN_H
