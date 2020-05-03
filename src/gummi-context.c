/**
 * @file   gummi-context.h
 * @brief  The Gummi Application Context
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

#include "gummi-context.h"
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
    GummiProject* project;
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