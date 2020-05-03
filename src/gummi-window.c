/**
 * @file   app-win.c
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

#include <gtk/gtk.h>

#include "gummi-app.h"
#include "gummi-window.h"


struct _GummiAppWindow
{
    GtkApplicationWindow parent;

    GSettings *settings;
    GtkWidget *stack;
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
new_project (GSimpleAction *action,
             GVariant      *parameter,
             gpointer       app)
{

}

static void
open_project (GSimpleAction *action,
              GVariant      *parameter,
              gpointer       app)
{

}

static void
close_project (GSimpleAction *action,
               GVariant      *parameter,
               gpointer       app)
{

}

static void
user_guide (GSimpleAction *action,
            GVariant      *parameter,
            gpointer       app)
{

}

static void
about_gummi (GSimpleAction *action,
            GVariant      *parameter,
            gpointer       app)
{

}


static GActionEntry win_entries[] =
        {
                { "new-project", new_project, NULL, NULL, NULL },
                { "open-project", open_project, NULL, NULL, NULL },
                { "close-project", close_project, NULL, NULL, NULL },
                { "user-guide", user_guide, NULL, NULL, NULL },
                { "about", about_gummi, NULL, NULL, NULL }
        };


static void
gummi_app_window_init(GummiAppWindow *win)
{

    gtk_widget_init_template (GTK_WIDGET (win));
    win->settings = g_settings_new ("org.gummi.app");


    g_action_map_add_action_entries (G_ACTION_MAP (win),
                                     win_entries, G_N_ELEMENTS (win_entries),
                                     win);
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
                                                 "/org/gummi/app/data/ui/window.ui");

    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, stack);
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


}
