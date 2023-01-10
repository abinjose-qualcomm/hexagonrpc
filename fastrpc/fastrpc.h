/*
 * FastRPC API Replacement - header files
 *
 * Copyright (C) 2023 Richard Acayan
 *
 * This file is part of sensh.
 *
 * Sensh is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef FASTRPC_H
#define FASTRPC_H

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

// See fastrpc.git/inc/remote.h
#define REMOTE_SCALARS_MAKEX(nAttr,nMethod,nIn,nOut,noIn,noOut) \
          ((((uint32_t)   (nAttr) &  0x7) << 29) | \
           (((uint32_t) (nMethod) & 0x1f) << 24) | \
           (((uint32_t)     (nIn) & 0xff) << 16) | \
           (((uint32_t)    (nOut) & 0xff) <<  8) | \
           (((uint32_t)    (noIn) & 0x0f) <<  4) | \
            ((uint32_t)   (noOut) & 0x0f))

#define REMOTE_SCALARS_MAKE(nMethod,nIn,nOut)  REMOTE_SCALARS_MAKEX(0,nMethod,nIn,nOut,0,0)

struct fastrpc_context {
	int fd;
	uint32_t handle;
};

struct fastrpc_function_def_interp2 {
	uint32_t msg_id;
	uint8_t in_nums;
	uint8_t in_bufs;
	uint8_t out_nums;
	uint8_t out_bufs;
};

struct fastrpc_context *fastrpc_create_context(int fd, uint32_t handle);

static inline void fastrpc_destroy_context(struct fastrpc_context *ctx)
{
	free(ctx);
}

int vfastrpc2(const struct fastrpc_function_def_interp2 *def,
	      int fd, uint32_t handle, va_list arg_list);
int vfastrpc(const struct fastrpc_function_def_interp2 *def,
	     const struct fastrpc_context *ctx, va_list arg_list);
int fastrpc2(const struct fastrpc_function_def_interp2 *def,
	     int fd, uint32_t handle, ...);
int fastrpc(const struct fastrpc_function_def_interp2 *def,
	    const struct fastrpc_context *ctx, ...);

#endif
