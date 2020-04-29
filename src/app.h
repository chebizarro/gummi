// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)

#ifndef GUMMI_APP_H
#define GUMMI_APP_H

#include <gtk/gtk.h>


#define GUMMI_APP_TYPE (gummi_app_get_type ())
G_DECLARE_FINAL_TYPE (GummiApp, gummi_app, GUMMI, APP, GtkApplication)


GummiApp     *gummi_app_new(void);


#endif //GUMMI_APP_H
