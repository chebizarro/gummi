// gummi
// Copyright (c) 2020 Chris Daley <chebizarro@gmail.com>
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "context.h"
#include "project.h"
#include "tabmanager.h"
#include "snippets.h"
#include "template.h"
#include "biblio.h"
#include "latex.h"
#include "iofunctions.h"

struct _GummiContext
{
    GObject parent_instance;

    GuEditor* editor;
    GuIOFunc* io;
    GuMotion* motion;
    GuLatex* latex;
    GuBiblio* biblio;
    GuTemplate* templ;
    GuSnippets* snippets;
    GuTabmanager* tabmanager;
    GuProject* project;
};

G_DEFINE_TYPE (GummiContext, gummi_context, G_TYPE_OBJECT)

static void
gummi_context_dispose (GObject *gobject)
{
    G_OBJECT_CLASS (gummi_context_parent_class)->dispose (gobject);
}

static void
gummi_context_finalize (GObject *gobject)
{
    G_OBJECT_CLASS (gummi_context_parent_class)->finalize (gobject);
}

static void
gummi_context_class_init (GummiContextClass *klass)
{

}

static void
gummi_context_init (GummiContext *self)
{

    self->motion = motion_init ();
    self->io = iofunctions_init();
    self->latex = latex_init ();
    //GuBiblio* biblio = biblio_init (builder);
    //GuTemplate* templ = template_init (builder);
    self->tabmanager = tabmanager_init ();
    self->project = project_init ();
    self->snippets = snippets_init ();


}

GummiContext *
gummi_context_new(void) {
    return g_object_new (GUMMI_TYPE_CONTEXT,
                         NULL);

}