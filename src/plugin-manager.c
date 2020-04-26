// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)

//#include "config.h"

#include "plugin-manager.h"

struct _GummiPluginsEngine
{
    PeasEngine parent_instance;

    GSettings *plugin_settings;
};

G_DEFINE_TYPE (GummiPluginsEngine, gummi_plugins_engine, PEAS_TYPE_ENGINE)

static GummiPluginsEngine *default_engine = NULL;

static void
gummi_plugins_engine_init (GummiPluginsEngine *engine)
{
    gchar *typelib_dir;
    GError *error = NULL;

    peas_engine_enable_loader (PEAS_ENGINE (engine), "python3");

    engine->plugin_settings = g_settings_new ("org.gnome.gummi.plugins");

    /* Require gummi's typelib. */
    typelib_dir = g_build_filename (gummi_dirs_get_gummi_lib_dir (),
                                    "girepository-1.0",
                                    NULL);

    if (!g_irepository_require_private (g_irepository_get_default (),
                                        typelib_dir, "Gummi", "3.0", 0, &error))
    {
        g_warning ("Could not load Gummi repository: %s", error->message);
        g_error_free (error);
        error = NULL;
    }

    g_free (typelib_dir);

    /* This should be moved to libpeas */
    if (!g_irepository_require (g_irepository_get_default (),
                                "Peas", "1.0", 0, &error))
    {
        g_warning ("Could not load Peas repository: %s", error->message);
        g_error_free (error);
        error = NULL;
    }

    if (!g_irepository_require (g_irepository_get_default (),
                                "PeasGtk", "1.0", 0, &error))
    {
        g_warning ("Could not load PeasGtk repository: %s", error->message);
        g_error_free (error);
        error = NULL;
    }

    peas_engine_add_search_path (PEAS_ENGINE (engine),
                                 gummi_dirs_get_user_plugins_dir (),
                                 gummi_dirs_get_user_plugins_dir ());

    peas_engine_add_search_path (PEAS_ENGINE (engine),
                                 gummi_dirs_get_gummi_plugins_dir (),
                                 gummi_dirs_get_gummi_plugins_data_dir ());

    g_settings_bind (engine->plugin_settings,
                     GUMMI_SETTINGS_ACTIVE_PLUGINS,
                     engine,
                     "loaded-plugins",
                     G_SETTINGS_BIND_DEFAULT);
}

static void
gummi_plugins_engine_dispose (GObject *object)
{
    GummiPluginsEngine *engine = GUMMI_PLUGINS_ENGINE (object);

    g_clear_object (&engine->plugin_settings);

    G_OBJECT_CLASS (gummi_plugins_engine_parent_class)->dispose (object);
}

static void
gummi_plugins_engine_class_init (GummiPluginsEngineClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->dispose = gummi_plugins_engine_dispose;
}

GummiPluginsEngine *
gummi_plugins_engine_get_default (void)
{
    if (default_engine == NULL)
    {
        default_engine = GUMMI_PLUGINS_ENGINE (g_object_new (GUMMI_TYPE_PLUGINS_ENGINE,
                                                             NULL));

        g_object_add_weak_pointer (G_OBJECT (default_engine),
                                   (gpointer) &default_engine);
    }

    return default_engine;
}
