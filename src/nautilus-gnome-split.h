/*
 * nautilus-gnome-split.h
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
#ifndef NAUTILUS_GNOME_SPLIT_H
#define NAUTILUS_GNOME_SPLIT_H

#include <glib-object.h>

G_BEGIN_DECLS

#define NAUTILUS_TYPE_GNOME_SPLIT  (nautilus_gnome_split_get_type ())
#define NAUTILUS_GNOME_SPLIT(o)    (G_TYPE_CHECK_INSTANCE_CAST ((o), NAUTILUS_TYPE_GNOME_SPLIT, NautilusGnomeSplit))
#define NAUTILUS_IS_GNOME_SPLIT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), NAUTILUS_TYPE_GNOME_SPLIT))
typedef struct _NautilusGnomeSplit      NautilusGnomeSplit;
typedef struct _NautilusGnomeSplitClass NautilusGnomeSplitClass;

struct _NautilusGnomeSplit {
    GObject parent_slot;
};

struct _NautilusGnomeSplitClass {
    GObjectClass parent_slot;
};

GType nautilus_gnome_split_get_type(void);
void nautilus_gnome_split_register_type(GTypeModule *module);

G_END_DECLS

#endif
