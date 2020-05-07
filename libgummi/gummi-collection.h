/*
 * gummi-collection.h
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



#ifndef GUMMI_GUMMI_COLLECTION_H
#define GUMMI_GUMMI_COLLECTION_H

#include <glib-object.h>

G_BEGIN_DECLS

#define GUMMI_TYPE_COLLECTION gummi_collection_get_type()
G_DECLARE_FINAL_TYPE(GummiCollection, gummi_collection, GUMMI, COLLECTION, GObject)

GummiCollection *gummi_collection_new (GType t_type);
gint gummi_collection_get_count(GummiCollection *collection);

G_END_DECLS

#endif //GUMMI_GUMMI_COLLECTION_H