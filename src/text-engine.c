/* text-engine.c
 *
 * Copyright 2022 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#include "text-engine.h"

#include "ui/inspector.h"

#include <gio/gio.h>

void
text_engine_init ()
{
    // Add a GTK Inspector page for debugging documents
    if (g_io_extension_point_lookup ("gtk-inspector-page"))
    g_io_extension_point_implement ("gtk-inspector-page",
                                    TEXT_TYPE_INSPECTOR,
                                    "text-engine",
                                    10);

}
