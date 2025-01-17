/* demo.c
 *
 * Copyright 2022 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <adwaita.h>

#include <text-engine.h>

#include <ui/display.h>
#include <format/import.h>

#define DEMO_TYPE_WINDOW demo_window_get_type ()
G_DECLARE_FINAL_TYPE (DemoWindow, demo_window, DEMO, WINDOW, AdwApplicationWindow)

struct _DemoWindow
{
    AdwApplicationWindow parent_instance;
};

G_DEFINE_FINAL_TYPE (DemoWindow, demo_window, ADW_TYPE_APPLICATION_WINDOW)

enum {
    PROP_0,
    N_PROPS
};

static GParamSpec *properties [N_PROPS];

static void
demo_window_finalize (GObject *object)
{
    DemoWindow *self = (DemoWindow *)object;

    G_OBJECT_CLASS (demo_window_parent_class)->finalize (object);
}

static void
demo_window_get_property (GObject    *object,
                          guint       prop_id,
                          GValue     *value,
                          GParamSpec *pspec)
{
    DemoWindow *self = DEMO_WINDOW (object);

    switch (prop_id)
    {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
demo_window_set_property (GObject      *object,
                          guint         prop_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
    DemoWindow *self = DEMO_WINDOW (object);

    switch (prop_id)
    {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
demo_window_class_init (DemoWindowClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = demo_window_finalize;
    object_class->get_property = demo_window_get_property;
    object_class->set_property = demo_window_set_property;
}

static void
demo_window_init (DemoWindow *self)
{
    TextFrame *frame;
    TextDisplay *display;
    const gchar *test;

    GtkWidget *header_bar;
    GtkWidget *vbox;
    GtkWidget *inspector_btn;

    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    adw_application_window_set_content (ADW_APPLICATION_WINDOW (self), vbox);

    // Example rich text document (uses html subset)
    test = "<p>There was an Old Man with a beard\nWho said, &quot;It is just as I feared!</p><p> &gt; Two Owls and a Hen,<br> &gt; Four Larks and a Wren,</p><p>Have all built their nests in my beard!&quot;</p>";
    frame = format_parse_html (test);

    header_bar = adw_header_bar_new ();
    display = text_display_new (frame);

    gtk_box_append (GTK_BOX (vbox), header_bar);
    gtk_box_append (GTK_BOX (vbox), GTK_WIDGET (display));

    inspector_btn = gtk_button_new_with_label ("Inspector");
    g_signal_connect_swapped (inspector_btn,
                              "clicked",
                              G_CALLBACK (gtk_window_set_interactive_debugging),
                              (gpointer) TRUE);

    adw_header_bar_pack_start (ADW_HEADER_BAR (header_bar), inspector_btn);
}

static void
demo_activate (GApplication *app)
{
    GtkWindow *window;

    g_assert (G_IS_APPLICATION (app));

    // Initialise text-engine for inspector page
    text_engine_init ();

    // Add CSS Stylesheet
    GtkCssProvider *css_provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_resource (css_provider, "/com/mattjakeman/TextEngine/Demo/style.css");

    GdkDisplay *display = gdk_display_get_default ();
    gtk_style_context_add_provider_for_display (display, GTK_STYLE_PROVIDER (css_provider),
                                                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Get the current window or create one if necessary.
    window = gtk_application_get_active_window (GTK_APPLICATION (app));

    if (window == NULL)
        window = g_object_new (DEMO_TYPE_WINDOW,
                               "application", app,
                               "default-width", 500,
                               "default-height", 500,
                               NULL);

    // Ask the window manager/compositor to present the window.
    gtk_window_present (window);
}

int
main (int argc, char **argv)
{
    AdwApplication *app;
    int ret;

    app = adw_application_new ("com.mattjakeman.TextEngine.Demo", G_APPLICATION_FLAGS_NONE);

    g_signal_connect (app, "activate", G_CALLBACK (demo_activate), NULL);

    ret = g_application_run (G_APPLICATION (app), argc, argv);

    g_clear_object (&app);

    return ret;
}
