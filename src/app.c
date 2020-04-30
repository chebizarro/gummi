// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)


#include <gtk/gtk.h>

#include "app.h"
#include "app-win.h"
#include "prefs.h"
#include "constants.h"
#include "signals.h"
#include "context.h"

struct _GummiApp
{
    GtkApplication parent;
    GummiContext *context;
};

G_DEFINE_TYPE(GummiApp, gummi_app, GTK_TYPE_APPLICATION);

static void
gummi_app_init (GummiApp *app)
{
}

static void
preferences_activated (GSimpleAction *action,
                       GVariant      *parameter,
                       gpointer       app)
{
    GummiPrefs *prefs;
    GtkWindow *win;

    win = gtk_application_get_active_window (GTK_APPLICATION (app));
    prefs = gummi_prefs_new(GUMMI_APP_WINDOW(win));
    gtk_window_present (GTK_WINDOW (prefs));
}

static void
quit_activated (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       app)
{
    g_application_quit (G_APPLICATION (app));
}

static GActionEntry app_entries[] =
        {
                { "preferences", preferences_activated, NULL, NULL, NULL },
                { "quit", quit_activated, NULL, NULL, NULL }
        };

static void
gummi_app_startup (GApplication *app)
{
    GtkBuilder *builder;
    GMenuModel *app_menu;
    const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };

    G_APPLICATION_CLASS (gummi_app_parent_class)->startup (app);

    g_action_map_add_action_entries (G_ACTION_MAP (app),
                                     app_entries, G_N_ELEMENTS (app_entries),
                                     app);
    gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                           "app.quit",
                                           quit_accels);

    builder = gtk_builder_new_from_resource ("/org/gtk/gummi/data/ui/app-menu.ui");
    app_menu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
    gtk_application_set_app_menu (GTK_APPLICATION (app), app_menu);

    /* Initialize signals */
    gummi_signals_register();

    GummiContext *ctx = gummi_context_new();
    GUMMI_APP(app)->context = ctx;

    /* Initialize logging */
    slog_init (0);
    slog (L_INFO, C_PACKAGE_NAME" version: "C_PACKAGE_VERSION"\n");



    /* Clean up references */
    g_object_unref (builder);
}

static void
gummi_app_activate (GApplication *app)
{
    GummiAppWindow *win;

    win = gummi_app_window_new(GUMMI_APP(app));
    gtk_window_present (GTK_WINDOW (win));
    slog_set_gui_parent (GTK_WINDOW(win));
    slog (L_DEBUG, "GummiGui created!\n");

}

static void
gummi_app_open (GApplication *app,
               GFile **files,
               gint n_files,
               const gchar *hint)
{
    GList *windows;
    GummiAppWindow *win;
    int i;

    windows = gtk_application_get_windows (GTK_APPLICATION (app));
    if (windows)
        win = GUMMI_APP_WINDOW (windows->data);
    else
        win = gummi_app_window_new(GUMMI_APP(app));

    for (i = 0; i < n_files; i++)
        gummi_app_window_open(win, files[i]);

    gtk_window_present (GTK_WINDOW (win));
}

static void
gummi_app_shutdown (GApplication *app) {

    g_object_unref (GUMMI_APP(app)->context);

    G_APPLICATION_CLASS(gummi_app_parent_class)->shutdown(app);
}

static void
gummi_app_class_init (GummiAppClass *class)
{
    G_APPLICATION_CLASS (class)->startup = gummi_app_startup;
    G_APPLICATION_CLASS (class)->activate = gummi_app_activate;
    G_APPLICATION_CLASS (class)->open = gummi_app_open;
    G_APPLICATION_CLASS (class)->shutdown = gummi_app_shutdown;
}

GummiApp *
gummi_app_new(void)
{
    return g_object_new (GUMMI_APP_TYPE,
                         "application-id", "org.gtk.gummi",
                         "flags", G_APPLICATION_HANDLES_OPEN,
                         NULL);
}