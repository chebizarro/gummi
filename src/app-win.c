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
    GtkWidget *searchbar;
    GtkWidget *searchentry;
    GtkWidget *gears;
    GtkWidget *sidebar;
    GtkWidget *words;
    GtkWidget *lines;
    GtkWidget *lines_label;
};

G_DEFINE_TYPE (GummiAppWindow, gummi_app_window, GTK_TYPE_APPLICATION_WINDOW)

static void
search_text_changed (GtkEntry         *entry,
                     GummiAppWindow *win)
{
    const gchar *text;
    GtkWidget *tab;
    GtkWidget *view;
    GtkTextBuffer *buffer;
    GtkTextIter start, match_start, match_end;

    text = gtk_entry_get_text (entry);

    if (text[0] == '\0')
        return;

    tab = gtk_stack_get_visible_child (GTK_STACK (win->stack));
    view = gtk_bin_get_child (GTK_BIN (tab));
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    /* Very simple-minded search implementation */
    gtk_text_buffer_get_start_iter (buffer, &start);
    if (gtk_text_iter_forward_search (&start, text, GTK_TEXT_SEARCH_CASE_INSENSITIVE,
                                      &match_start, &match_end, NULL))
    {
        gtk_text_buffer_select_range (buffer, &match_start, &match_end);
        gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW (view), &match_start,
                                      0.0, FALSE, 0.0, 0.0);
    }
}

static void
find_word (GtkButton        *button,
           GummiAppWindow *win)
{
    const gchar *word;

    word = gtk_button_get_label (button);
    gtk_entry_set_text (GTK_ENTRY (win->searchentry), word);
}

static void
update_words (GummiAppWindow *win)
{
    GHashTable *strings;
    GHashTableIter iter;
    GtkWidget *tab, *view, *row;
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    GList *children, *l;
    gchar *word, *key;

    tab = gtk_stack_get_visible_child (GTK_STACK (win->stack));

    if (tab == NULL)
        return;

    view = gtk_bin_get_child (GTK_BIN (tab));
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    strings = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);

    gtk_text_buffer_get_start_iter (buffer, &start);
    while (!gtk_text_iter_is_end (&start))
    {
        while (!gtk_text_iter_starts_word (&start))
        {
            if (!gtk_text_iter_forward_char (&start))
                goto done;
        }
        end = start;
        if (!gtk_text_iter_forward_word_end (&end))
            goto done;
        word = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
        g_hash_table_add (strings, g_utf8_strdown (word, -1));
        g_free (word);
        start = end;
    }

    done:
    children = gtk_container_get_children (GTK_CONTAINER (win->words));
    for (l = children; l; l = l->next)
        gtk_container_remove (GTK_CONTAINER (win->words), GTK_WIDGET (l->data));
    g_list_free (children);

    g_hash_table_iter_init (&iter, strings);
    while (g_hash_table_iter_next (&iter, (gpointer *)&key, NULL))
    {
        row = gtk_button_new_with_label (key);
        g_signal_connect (row, "clicked",
                          G_CALLBACK (find_word), win);
        gtk_container_add (GTK_CONTAINER (win->words), row);
    }

    g_hash_table_unref (strings);
}

static void
update_lines (GummiAppWindow *win)
{
    GtkWidget *tab, *view;
    GtkTextBuffer *buffer;
    int count;
    gchar *lines;

    tab = gtk_stack_get_visible_child (GTK_STACK (win->stack));

    if (tab == NULL)
        return;

    view = gtk_bin_get_child (GTK_BIN (tab));
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    count = gtk_text_buffer_get_line_count (buffer);
    lines = g_strdup_printf ("%d", count);
    gtk_label_set_text (GTK_LABEL (win->lines), lines);
    g_free (lines);
}

static void
visible_child_changed (GObject          *stack,
                       GParamSpec       *pspec,
                       GummiAppWindow *win)
{
    if (gtk_widget_in_destruction (GTK_WIDGET (stack)))
        return;

    gtk_search_bar_set_search_mode (GTK_SEARCH_BAR (win->searchbar), FALSE);
    update_words (win);
    update_lines (win);
}

static void
words_changed (GObject          *sidebar,
               GParamSpec       *pspec,
               GummiAppWindow *win)
{
    update_words (win);
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

    g_settings_bind (win->settings, "show-words",
                     win->sidebar, "reveal-child",
                     G_SETTINGS_BIND_DEFAULT);

    g_object_bind_property (win->search, "active",
                            win->searchbar, "search-mode-enabled",
                            G_BINDING_BIDIRECTIONAL);

    g_signal_connect (win->sidebar, "notify::reveal-child",
                      G_CALLBACK (words_changed), win);

    builder = gtk_builder_new_from_resource ("/org/gtk/gummi/data/ui/gears-menu.ui");
    menu = G_MENU_MODEL (gtk_builder_get_object (builder, "menu"));
    gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (win->gears), menu);
    g_object_unref (builder);

    action = g_settings_create_action (win->settings, "show-words");
    g_action_map_add_action (G_ACTION_MAP (win), action);
    g_object_unref (action);

    action = (GAction*) g_property_action_new ("show-lines", win->lines, "visible");
    g_action_map_add_action (G_ACTION_MAP (win), action);
    g_object_unref (action);

    g_object_bind_property (win->lines, "visible",
                            win->lines_label, "visible",
                            G_BINDING_DEFAULT);
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
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, search);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, searchbar);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, searchentry);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, gears);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, words);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, sidebar);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, lines);
    gtk_widget_class_bind_template_child (GTK_WIDGET_CLASS (class), GummiAppWindow, lines_label);

    gtk_widget_class_bind_template_callback (GTK_WIDGET_CLASS (class), search_text_changed);
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

    update_words (win);
    update_lines (win);
}
