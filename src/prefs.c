// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)

#include <gtk/gtk.h>

#include "gummi-app.h"
#include "gummi-window.h"
#include "prefs.h"

struct _GummiPrefs
{
    GtkDialog parent;

    GSettings *settings;
    GtkWidget *font;
    GtkWidget *transition;
};

G_DEFINE_TYPE (GummiPrefs, gummi_prefs, GTK_TYPE_DIALOG)

static void
gummi_prefs_init (GummiPrefs *prefs)
{
    gtk_widget_init_template (GTK_WIDGET (prefs));
    prefs->settings = g_settings_new ("org.gummi.app");

    g_settings_bind (prefs->settings, "font",
                     prefs->font, "font",
                     G_SETTINGS_BIND_DEFAULT);
    g_settings_bind (prefs->settings, "transition",
                     prefs->transition, "active-id",
                     G_SETTINGS_BIND_DEFAULT);
}

static void
gummi_prefs_dispose(GObject *object)
{
    GummiPrefs *prefs;

    prefs = GUMMI_PREFS (object);

    g_clear_object (&prefs->settings);

    G_OBJECT_CLASS (gummi_prefs_parent_class)->dispose (object);
}

static void
gummi_prefs_class_init(GummiPrefsClass *class)
{
    G_OBJECT_CLASS (class)->dispose = gummi_prefs_dispose;

    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                                 "/org/gummi/app/data/ui/prefs.ui");
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiPrefs, font);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiPrefs, transition);
}

GummiPrefs *
gummi_prefs_new(GummiAppWindow *win)
{
    return g_object_new (GUMMI_PREFS_TYPE, "transient-for", win, "use-header-bar", TRUE, NULL);
}
