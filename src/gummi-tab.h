/*
 * gummi-tab.h
 * This file is part of gummi
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

#ifndef GUMMI_TAB_H
#define GUMMI_TAB_H

#include <gtksourceview/gtksource.h>

G_BEGIN_DECLS

typedef enum
{
	GUMMI_TAB_STATE_NORMAL = 0,
	GUMMI_TAB_STATE_LOADING,
	GUMMI_TAB_STATE_REVERTING,
	GUMMI_TAB_STATE_SAVING,
	GUMMI_TAB_STATE_PRINTING,
	GUMMI_TAB_STATE_SHOWING_PRINT_PREVIEW,
	GUMMI_TAB_STATE_LOADING_ERROR,
	GUMMI_TAB_STATE_REVERTING_ERROR,
	GUMMI_TAB_STATE_SAVING_ERROR,
	GUMMI_TAB_STATE_GENERIC_ERROR,
	GUMMI_TAB_STATE_CLOSING,
	GUMMI_TAB_STATE_EXTERNALLY_MODIFIED_NOTIFICATION,
	GUMMI_TAB_NUM_OF_STATES /* This is not a valid state */
} GummiTabState;

#define GUMMI_TYPE_TAB (gummi_tab_get_type())

G_DECLARE_FINAL_TYPE (GummiTab, gummi_tab, GEDIT, TAB, GtkBox)

//GummiView *gummi_tab_get_view (GummiTab *tab);

//GummiDocument *gummi_tab_get_document (GummiTab *tab);

//GummiTab *gummi_tab_get_from_document (GummiDocument *doc);

GummiTabState gummi_tab_get_state (GummiTab *tab);

gboolean gummi_tab_get_auto_save_enabled (GummiTab *tab);

void gummi_tab_set_auto_save_enabled (GummiTab *tab,
							 gboolean enable);

gint gummi_tab_get_auto_save_interval (GummiTab *tab);

void gummi_tab_set_auto_save_interval (GummiTab *tab,
							 gint interval);

void gummi_tab_set_info_bar (GummiTab *tab,
							 GtkWidget *info_bar);

G_END_DECLS

#endif  /* GUMMI_TAB_H  */

