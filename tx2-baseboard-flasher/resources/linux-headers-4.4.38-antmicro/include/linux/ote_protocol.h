/*
 * Copyright (c) 2013-2015 NVIDIA Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __OTE_PROTOCOL_H__
#define __OTE_PROTOCOL_H__

int tegra_set_vpr_params(void *vpr_base, size_t vpr_size);

void te_restore_keyslots(void);
int  te_vrr_set_buf(phys_addr_t addr);
void te_vrr_sec(void);

#endif
