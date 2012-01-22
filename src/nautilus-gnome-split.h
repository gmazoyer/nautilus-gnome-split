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
