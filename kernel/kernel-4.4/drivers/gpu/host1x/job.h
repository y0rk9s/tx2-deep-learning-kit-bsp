/*
 * Tegra host1x Job
 *
 * Copyright (C) 2010-2016 NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __HOST1X_JOB_H
#define __HOST1X_JOB_H

struct sync_fence;

struct host1x_job_gather {
	u32 words;
	u32 class_id;
	dma_addr_t base;
	struct host1x_bo *bo;
	u32 offset;
	bool handled;
	struct sync_fence *pre_fence;
};

struct host1x_cmdbuf {
	u32 handle;
	u32 offset;
	u32 words;
	u32 pad;
};

struct host1x_waitchk {
	struct host1x_bo *bo;
	u32 offset;
	u32 syncpt_id;
	u32 thresh;
};

struct host1x_job_unpin_data {
	struct host1x_bo *bo;
	struct sg_table *sgt;
};

void host1x_job_set_notifier(struct host1x_job *job, u32 error);

/*
 * Dump contents of job to debug output.
 */
void host1x_job_dump(struct device *dev, struct host1x_job *job);

#endif
