/*
 * gummi-collection.c
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


#include "gummi-collection.h"

struct _GummiCollection
{
    GObject parent_instance;

    GHashTable *data;
};


G_DEFINE_TYPE(GummiCollection, gummi_collection, G_TYPE_OBJECT)

enum
{
    PROP_TYPE = 1,
    PROP_COUNT,
    N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

static void _gummi_collection_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _gummi_collection_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);


static void
gummi_collection_class_init (GummiCollectionClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    g_signal_new ("added", GUMMI_TYPE_COLLECTION, G_SIGNAL_RUN_LAST, 0, NULL, NULL, NULL, G_TYPE_NONE, 2, G_TYPE_STRING, NULL);

    G_OBJECT_CLASS (klass)->get_property = _gummi_collection_get_property;
    G_OBJECT_CLASS (klass)->set_property = _gummi_collection_set_property;

    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_TYPE, g_param_spec_object ("t_type", "type", "type", G_TYPE_BOXED, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_CONSTRUCT_ONLY));
    g_object_class_install_property (G_OBJECT_CLASS (klass), PROP_COUNT, g_param_spec_object ("count", "count", "count", G_TYPE_INT, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));

}


static void _gummi_collection_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
    GummiCollection *self;
    self = G_TYPE_CHECK_INSTANCE_CAST(object, GUMMI_TYPE_COLLECTION, GummiCollection);
    switch (property_id) {

        case PROP_TYPE:

            break;
        case PROP_COUNT:
            g_value_set_int (value, gummi_collection_get_count(self));
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
            break;
    }
}

static void _gummi_collection_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {

}

gint gummi_collection_get_count(GummiCollection *collection) {
    return g_hash_table_size(collection->data);
}


static void
gummi_collection_init(GummiCollection *self) {

}

static void
gummi_collection_finalize (GObject *gobject)
{
    GummiCollection *self = G_TYPE_CHECK_INSTANCE_CAST(gobject, GUMMI_TYPE_COLLECTION, GummiCollection);
    g_object_unref(self->data);
    G_OBJECT_CLASS (gummi_collection_parent_class)->finalize (gobject);
}


GummiCollection *gummi_collection_new (GType t_type) {


}
