/* icons.c  - GPA icons
 * Copyright (C) 2000 OpenIT GmbH
  *
 * This file is part of GPA
 *
 * GPA is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GPA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include "icons.h"
#include "icons.xpm"


struct {
  const char *name;
  char **xpm;
} xpms[] = {
  { "openfile", openfile_xpm  },
  { "help",     help_xpm  },
  { "encrypt",          encrypt_xpm  },
  { "decrypt",          decrypt_xpm  },
  { "sign",          sign_xpm  },
  { "gpa_sign_small",          gpa_sign_small_xpm  },
  { "keyring",          keyring_xpm  },
  { "trash",          trash_xpm  },
  { "gpa_trust_fully",          gpa_trust_fully_xpm },
  { "gpa_trust_marginal",        gpa_trust_marginally_xpm },
  { "gpa_dont_trust",        gpa_dont_trust_xpm },
  { "gpa_trust_unknown",        gpa_trust_unknown_xpm },
  { NULL, NULL }
};



static GdkPixmap *
pixmap_for_icon ( GtkWidget *window, const char *name, GdkBitmap **r_mask )
{
    GtkStyle  *style;
    GdkPixmap *pix;
    char **xpm = NULL;
    int i;
    

    for ( i=0; xpms[i].name ; i++ )
      if ( !strcmp ( xpms[i].name, name ) )
        {
          xpm = xpms[i].xpm;
          break;
        }
    
    if ( !xpm )
      {
        fprintf (stderr, "Icon `%s' not found\n", name );
        return NULL;
      }
    
    
    style = gtk_widget_get_style (window);
    pix = gdk_pixmap_create_from_xpm_d (window->window, r_mask,
                                        &style->bg[GTK_STATE_NORMAL],
                                        xpm);
    return pix;
}

GtkWidget *
gpa_create_icon_widget ( GtkWidget *window, const char *name )
{
    GdkBitmap *mask;
    GtkWidget *icon = NULL;
    GdkPixmap *pix;

    pix = pixmap_for_icon ( window, name, &mask );
    if ( pix )
        icon = gtk_pixmap_new(pix, mask);
    return icon;
}

GdkPixmap *
gpa_create_icon_pixmap ( GtkWidget *window, const char *name, GdkBitmap **mask )
{
  return pixmap_for_icon ( window, name, mask );
}