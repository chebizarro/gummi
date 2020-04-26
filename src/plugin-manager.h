// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)

#ifndef GUMMI_PLUGIN_MANAGER_H
#define GUMMI_PLUGIN_MANAGER_H

#include <glib.h>
#include <libpeas/peas.h>

G_BEGIN_DECLS

#define GUMMI_TYPE_PLUGINS_ENGINE (gummi_plugins_engine_get_type ())
G_DECLARE_FINAL_TYPE(GummiPluginsEngine, gummi_plugins_engine, GUMMI, PLUGINS_ENGINE, PeasEngine)

GummiPluginsEngine	*gummi_plugins_engine_get_default	(void);

G_END_DECLS

#endif //GUMMI_PLUGIN_MANAGER_H
