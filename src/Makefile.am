AM_CPPFLAGS =						\
	-DG_LOG_DOMAIN=\"Nautilus-Gnome-Split\"	\
	-DDATADIR=\"$(datadir)\"			\
	-DGNOMELOCALEDIR=\""$(datadir)/locale"\" 	\
	-I$(top_srcdir)					\
	-I$(top_builddir)				\
	$(WARN_CFLAGS)                                  \
	$(DISABLE_DEPRECATED_CFLAGS)			\
	$(NAUTILUS_CFLAGS)

nautilus_extensiondir=$(NAUTILUS_EXTENSION_DIR)

nautilus_extension_LTLIBRARIES=libnautilus-gnome-split.la

libnautilus_gnome_split_la_SOURCES =				\
	gnome-split.c						\
	nautilus-gnome-split.c	nautilus-gnome-split.h

libnautilus_gnome_split_la_LDFLAGS = -module -avoid-version
libnautilus_gnome_split_la_LIBADD  = $(NAUTILUS_LIBS)
