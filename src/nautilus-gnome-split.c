#ifdef HAVE_CONFIG_H
 #include <config.h> /* for GETTEXT_PACKAGE */
#endif

#include "nautilus-gnome-split.h"

#include <libnautilus-extension/nautilus-menu-provider.h>

#include <glib/gi18n-lib.h>
#include <gtk/gtk.h>

#include <string.h> /* for strcmp */

static void nautilus_gnome_split_instance_init(NautilusGnomeSplit* img);
static void nautilus_gnome_split_class_init(NautilusGnomeSplitClass* class);
GList* nautilus_gnome_split_get_file_items(NautilusMenuProvider* provider,
                                           GtkWidget*            window,
                                           GList*                files);

static GType gnome_split_type = 0;

static gboolean gnome_split_file_is_mergeable(NautilusFileInfo* file_info) {
	gchar*   uri_scheme;
	gchar*   mime_type;
	gboolean mergeable;
	
	mergeable  = TRUE;
	uri_scheme = nautilus_file_info_get_uri_scheme(file_info);
	mime_type  = nautilus_file_info_get_mime_type(file_info);

	if (strcmp(uri_scheme, "file") != 0) {
		mergeable = FALSE;
	}

	g_free(uri_scheme);

	if (strncmp (mime_type, "image/", 6) != 0) {
		mergeable = FALSE;
	}

	g_free(mime_type);
	
	return mergeable;
}

static void gnome_split_merge_callback(NautilusMenuItem* item, GList* files) {
    GString* buffer;
    gchar*   command;

    buffer  = g_string_new("gnome-split --merge ");
    buffer  = g_string_append(buffer, g_file_get_path(files->data));
    command = buffer->str;

    g_string_free(buffer, FALSE);

    g_spawn_command_line_async(command, NULL);
}

static void gnome_split_split_callback(NautilusMenuItem* item, GList* files) {
    GString* buffer;
    gchar*   command;

    buffer  = g_string_new("gnome-split --split ");
    buffer  = g_string_append(buffer, g_file_get_path(files->data));
    command = buffer->str;

    g_string_free(buffer, FALSE);

    g_spawn_command_line_async(command, NULL);
}

static GList* nautilus_gnome_split_get_background_items(
    NautilusMenuProvider* provider,
    GtkWidget*            window,
    NautilusFileInfo*     file_info) {
    return NULL;
}

GList* nautilus_gnome_split_get_file_items(NautilusMenuProvider* provider,
                                           GtkWidget*            window,
                                           GList*                files) {
    NautilusMenuItem* item;
    GList*            items;

    items = NULL;

    if (g_list_length(files) == 1) {
        if (gnome_split_file_is_mergeable(files->data)) {
            item = nautilus_menu_item_new("NautilusGnomeSplit::merge",
                        _("_Merge Files..."),
                        _("Merge all files together"),
                        "");
            g_signal_connect(item, "activate",
                        G_CALLBACK(gnome_split_merge_callback),
                        nautilus_file_info_list_copy(files));
		} else {
            item = nautilus_menu_item_new("NautilusGnomeSplit::split",
                        _("_Split File..."),
                        _("Split this file"),
                        "");
            g_signal_connect(item, "activate",
                        G_CALLBACK(gnome_split_split_callback),
                        nautilus_file_info_list_copy(files));
		}

        items = g_list_append(items, item);

        return items;
    }
	
	return NULL;
}

static void nautilus_gnome_split_menu_provider_iface_init(
    NautilusMenuProviderIface* iface) {
    iface->get_background_items = nautilus_gnome_split_get_background_items;
    iface->get_file_items       = nautilus_gnome_split_get_file_items;
}

static void nautilus_gnome_split_instance_init(NautilusGnomeSplit* this) {
}

static void nautilus_gnome_split_class_init(NautilusGnomeSplitClass* class) {
}

GType nautilus_gnome_split_get_type(void) {
    return gnome_split_type;
}

void nautilus_gnome_split_register_type(GTypeModule* module) {
    static const GTypeInfo info = {
        sizeof(NautilusGnomeSplitClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) nautilus_gnome_split_class_init,
        NULL,
        NULL,
        sizeof(NautilusGnomeSplit),
        0,
        (GInstanceInitFunc) nautilus_gnome_split_instance_init
    };

    static const GInterfaceInfo menu_provider_iface_info = {
        (GInterfaceInitFunc) nautilus_gnome_split_menu_provider_iface_init,
        NULL,
        NULL
    };

	gnome_split_type = g_type_module_register_type(module, G_TYPE_OBJECT,
                "NautilusGnomeSplit", &info, 0);

    g_type_module_add_interface(module, gnome_split_type,
                NAUTILUS_TYPE_MENU_PROVIDER, &menu_provider_iface_info);
}