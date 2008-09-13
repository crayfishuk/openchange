/*
   OpenChange Exchange Administration library.

   Copyright (C) Julien Kerihuel 2007.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libmapiadmin/libmapiadmin.h>
#include <libmapiadmin/proto_private.h>

/**
	\file
	Housekeeping functions for mapiadmin
*/

/**
	Create and initialise a mapiadmin_ctx structure

	You should use mapiadmin_release to clean up the mapiadmin_ctx
	structure when done.
*/
_PUBLIC_ struct mapiadmin_ctx *mapiadmin_init(void)
{
	struct mapiadmin_ctx	*mapiadmin_ctx;

	if (!global_mapi_ctx) return NULL;
	if (!global_mapi_ctx->session) return NULL;
	if (!global_mapi_ctx->session->profile) return NULL;

	mapiadmin_ctx = talloc_zero((TALLOC_CTX *)global_mapi_ctx, struct mapiadmin_ctx);

	mapiadmin_ctx->binding = talloc_asprintf((TALLOC_CTX *)mapiadmin_ctx, "ncacn_np:%s", 
						 global_mapi_ctx->session->profile->server);

	return mapiadmin_ctx;
}

/**
	Clean up a mapiadmin_ctx structure

	The structure is assumed to have been allocated uding mapiadmin_init() or
	equivalent code.
*/
_PUBLIC_ enum MAPISTATUS mapiadmin_release(struct mapiadmin_ctx *mapiadmin_ctx)
{
	MAPI_RETVAL_IF(!mapiadmin_ctx, MAPI_E_NOT_INITIALIZED, NULL);

	talloc_free(mapiadmin_ctx);

	return MAPI_E_SUCCESS;
}
