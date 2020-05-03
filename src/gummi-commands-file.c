/**
 * @file   gummi-commands-file.c
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


void on_menu_new_activate (GtkWidget *widget, void* user) {
    if (!gtk_widget_get_sensitive (GTK_WIDGET (gui->rightpane)))
        gui_set_hastabs_sensitive (TRUE);
    tabmanager_create_tab (A_NONE, NULL, NULL);
}


void on_menu_template_activate (GtkWidget *widget, void *user) {
    gtk_list_store_clear (gummi->templ->list_templates);
    template_setup (gummi->templ);
    gtk_widget_show_all (GTK_WIDGET (gummi->templ->templatewindow));
}

void on_menu_open_activate (GtkWidget *widget, void* user) {
    gchar *filename = NULL;

    if ( (filename = get_open_filename (TYPE_LATEX)))
        gui_open_file (filename);
    g_free (filename);

    if (g_active_editor)
        gtk_widget_grab_focus (GTK_WIDGET (g_active_editor->view));
}


void on_menu_save_activate (GtkWidget *widget, void* user) {
    gui_save_file (g_active_tab, FALSE);
}


void on_menu_saveas_activate (GtkWidget *widget, void* user) {
    gui_save_file (g_active_tab, TRUE);
}

void on_menu_export_activate (GtkWidget *widget, void *user) {
    gchar* filename = NULL;

    filename = get_save_filename (TYPE_PDF);
    if (filename)
        latex_export_pdffile (gummi->latex, g_active_editor, filename, TRUE);
    g_free (filename);
}

void on_menu_recent_activate (GtkWidget *widget, void *user) {
    const gchar* name = gtk_menu_item_get_label (GTK_MENU_ITEM (widget));
    gchar* tstr;
    gint index = name[0] - '0' -1;

    if (utils_path_exists (gui->recent_list[index])) {
        gui_open_file (gui->recent_list[index]);
    } else {
        tstr = g_strdup_printf (_("Error loading recent file: %s"),
                                gui->recent_list[index]);
        slog (L_ERROR, "%s\n", tstr);
        slog (L_G_ERROR, "Could not find the file %s.\n",
              gui->recent_list[index]);
        statusbar_set_message (tstr);
        g_free (tstr);
        g_free (gui->recent_list[index]);
        gui->recent_list[index] = NULL;
        while (index < RECENT_FILES_NUM -1) {
            gui->recent_list[index] = gui->recent_list[index+1];
            ++index;
        }
        gui->recent_list[RECENT_FILES_NUM -1] = g_strdup ("__NULL__");
    }
    display_recent_files (gui);
}