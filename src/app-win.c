// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)


#include <gtk/gtk.h>

#include "app.h"
#include "app-win.h"


struct _GummiAppWindow
{
    GtkApplicationWindow parent;

    GSettings *settings;
    GtkWidget *stack;
    GtkWidget *search;
    GtkWidget *gears;
};

G_DEFINE_TYPE (GummiAppWindow, gummi_app_window, GTK_TYPE_APPLICATION_WINDOW)


static void
visible_child_changed (GObject          *stack,
                       GParamSpec       *pspec,
                       GummiAppWindow *win)
{
    if (gtk_widget_in_destruction (GTK_WIDGET (stack)))
        return;

}


static void
gummi_app_window_init(GummiAppWindow *win)
{
    GtkBuilder *builder;
    GMenuModel *menu;
    GAction *action;

    gtk_widget_init_template (GTK_WIDGET (win));
    win->settings = g_settings_new ("org.gtk.gummi");

    g_settings_bind (win->settings, "transition",
                     win->stack, "transition-type",
                     G_SETTINGS_BIND_DEFAULT);

    builder = gtk_builder_new_from_resource ("/org/gtk/gummi/data/ui/gears-menu.ui");
    menu = G_MENU_MODEL (gtk_builder_get_object (builder, "menu"));
    gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (win->gears), menu);
    g_object_unref (builder);

}

static void
gummi_app_window_dispose(GObject *object)
{
    GummiAppWindow *win;

    win = GUMMI_APP_WINDOW (object);

    g_clear_object (&win->settings);

    G_OBJECT_CLASS (gummi_app_window_parent_class)->dispose (object);
}

static void
gummi_app_window_class_init (GummiAppWindowClass *class)
{
    G_OBJECT_CLASS (class)->dispose = gummi_app_window_dispose;

    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                                 "/org/gtk/gummi/data/ui/window.ui");

    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, stack);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, gears);
    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (class), visible_child_changed);
}

GummiAppWindow *
gummi_app_window_new(GummiApp *app)
{
    return g_object_new (GUMMI_APP_WINDOW_TYPE, "application", app, NULL);
}

void
gummi_app_window_open(GummiAppWindow *win,
                      GFile *file)
{
    gchar *basename;
    GtkWidget *scrolled, *view;
    gchar *contents;
    gsize length;
    GtkTextBuffer *buffer;
    GtkTextTag *tag;
    GtkTextIter start_iter, end_iter;

    basename = g_file_get_basename (file);

    scrolled = gtk_scrolled_window_new (NULL, NULL);
    gtk_widget_set_hexpand (scrolled, TRUE);
    gtk_widget_set_vexpand (scrolled, TRUE);
    view = gtk_text_view_new ();
    gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
    gtk_container_add (GTK_CONTAINER (scrolled), view);
    gtk_stack_add_titled (GTK_STACK (win->stack), scrolled, basename, basename);

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL))
    {
        gtk_text_buffer_set_text (buffer, contents, length);
        g_free (contents);
    }

    tag = gtk_text_buffer_create_tag (buffer, NULL, NULL);
    g_settings_bind (win->settings, "font",
                     tag, "font",
                     G_SETTINGS_BIND_DEFAULT);

    gtk_text_buffer_get_start_iter (buffer, &start_iter);
    gtk_text_buffer_get_end_iter (buffer, &end_iter);
    gtk_text_buffer_apply_tag (buffer, tag, &start_iter, &end_iter);

    g_free (basename);

    gtk_widget_set_sensitive (win->search, TRUE);

}
