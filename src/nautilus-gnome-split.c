/*
 * nautilus-gnome-split.c
 * 
 * Copyright (c) 2011 Guillaume Mazoyer
 * 
 * This file is part of GNOME Split Nautilus extension.
 * 
 * GNOME Split Nautilus extension is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * GNOME Split Nautilus extension is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNOME Split Nautilus extension.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
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
    gchar*   mime_type;
    gboolean mergeable;

    mergeable = FALSE;
    mime_type = nautilus_file_info_get_mime_type(file_info);

    if ((strcmp(mime_type, "application/x-extension-xtm") == 0) ||
        (strcmp(mime_type, "application/x-extension-gsp") == 0) ||
        (strcmp(mime_type, "application/x-extension-yct") == 0) ||
        (strcmp(mime_type, "application/x-extension-kk")  == 0) ||
        (strcmp(mime_type, "application/x-generic-chunk") == 0)) {
        mergeable = TRUE;
    }

    g_free(mime_type);

    return mergeable;
}

static void gnome_split_merge_callback(NautilusMenuItem* item, GList* files) {
    GString* buffer;
    GFile*   location;
    gchar*   command;

    buffer   = g_string_new("gnome-split --merge ");
    location = nautilus_file_info_get_location(files->data);

    g_string_append(buffer, g_file_get_path(location));
    g_object_unref(location);

    command = buffer->str;
    g_string_free(buffer, FALSE);

    g_spawn_command_line_async(command, NULL);
}

static void gnome_split_split_callback(NautilusMenuItem* item, GList* files) {
    GString* buffer;
    GFile*   location;
    gchar*   command;

    buffer   = g_string_new("gnome-split --split ");
    location = nautilus_file_info_get_location(files->data);

    g_string_append(buffer, g_file_get_path(location));
    g_object_unref(location);

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

    if ((g_list_length(files) == 1) && !nautilus_file_info_is_directory(files->data)) {
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
