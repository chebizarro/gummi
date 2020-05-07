/*
 * gummi-view.h
 * This file is part of gummi
 * 
 * Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GUMMI_VIEW_H
#define GUMMI_VIEW_H

#include <glib-object.h>

G_BEGIN_DECLS

#define GUMMI_TYPE_VIEW gummi_view_get_type ()
G_DECLARE_INTERFACE (GummiView, gummi_view, GUMMI, VIEW, GObject)

struct _GummiViewInterface
{
    GTypeInterface parent_iface;

};


G_END_DECLS

#endif // GUMMI_VIEW_H