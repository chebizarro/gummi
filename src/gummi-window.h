/**
 * @file   app-win.h
 * @brief  Main window implementation
 *
 * Copyright (C) 2009-2020 Gummi Developers
 * All Rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GUMMI_GUMMI_WINDOW_H
#define GUMMI_GUMMI_WINDOW_H

#include <gtk/gtk.h>
#include "gummi-app.h"


#define GUMMI_APP_WINDOW_TYPE (gummi_app_window_get_type ())
G_DECLARE_FINAL_TYPE (GummiAppWindow, gummi_app_window, GUMMI, APP_WINDOW, GtkApplicationWindow)


GummiAppWindow       *gummi_app_window_new (GummiApp *app);
void                 gummi_app_window_open (GummiAppWindow *win,
                                            GFile *file);


#endif //GUMMI_GUMMI_WINDOW_H
