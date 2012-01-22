#ifdef HAVE_CONFIG_H
 #include <config.h>
#endif

#include "nautilus-gnome-split.h"

#include <libintl.h>

static GType type_list[1];

void nautilus_module_initialize(GTypeModule* module);
void nautilus_module_shutdown(void);
void nautilus_module_list_types(const GType** types,
                                int*          num_types);

void nautilus_module_initialize(GTypeModule* module) {
    g_print("Initializing nautilus-gnome-split extension\n");

    nautilus_gnome_split_register_type(module);
    type_list[0] = NAUTILUS_TYPE_GNOME_SPLIT;

    bindtextdomain(GETTEXT_PACKAGE, GNOMELOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
}

void nautilus_module_shutdown(void) {
    g_print ("Shutting down nautilus-gnome-split extension\n");
}

void  nautilus_module_list_types(const GType** types,
                                 int*          num_types) {
    *types = type_list;
    *num_types = G_N_ELEMENTS(type_list);
}
