// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)

#ifndef GUMMI_CONTEXT_H
#define GUMMI_CONTEXT_H

#include <glib-object.h>

G_BEGIN_DECLS

#define GUMMI_TYPE_CONTEXT gummi_context_get_type ()
G_DECLARE_FINAL_TYPE (GummiContext, gummi_context, GUMMI, CONTEXT, GObject)

GummiContext *gummi_context_new (void);

G_END_DECLS

#endif //GUMMI_CONTEXT_H
