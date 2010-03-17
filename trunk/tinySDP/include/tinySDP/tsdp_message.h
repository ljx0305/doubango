/*
* Copyright (C) 2009 Mamadou Diop.
*
* Contact: Mamadou Diop <diopmamadou@yahoo.fr>
*	
* This file is part of Open Source Doubango Framework.
*
* DOUBANGO is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*	
* DOUBANGO is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*	
* You should have received a copy of the GNU General Public License
* along with DOUBANGO.
*
*/

/**@file tsdp_message.h
 * @brief SDP message.
 *
 * @author Mamadou Diop <diopmamadou(at)yahoo.fr>
 *
 * @date Created: Sat Nov 8 16:54:58 2009 mdiop
 */
#ifndef TINYSDP_MESSAGE_H
#define TINYSDP_MESSAGE_H

#include "tinySDP_config.h"

#include "tinySDP/headers/tsdp_header.h"

TSDP_BEGIN_DECLS

#define TSDP_MESSAGE_CREATE()	tsk_object_new(tsdp_message_def_t)

typedef struct tsdp_message_s
{
	TSK_DECLARE_OBJECT;

	//! List of @ref tsdp_header_t elements. 
	tsdp_headers_L_t* headers;
}
tsdp_message_t;

TINYSDP_API int tsdp_message_add_header(tsdp_message_t *self, const tsdp_header_t *hdr);
TINYSDP_API int tsdp_message_add_headers(tsdp_message_t *self, const tsdp_headers_L_t *headers);

#if !defined(_MSC_VER) || defined(__GNUC__)
static void TSDP_MESSAGE_ADD_HEADER(tsdp_message_t *self, ...)
	{
		va_list ap;
		tsdp_header_t *header;
		const tsk_object_def_t *objdef;
		
		va_start(ap, self);
		objdef = va_arg(ap, const tsk_object_def_t*);
		header = tsk_object_new2(objdef, &ap);
		va_end(ap);

		tsdp_message_add_header(self, header);
		tsk_object_unref(header);
	}
#else
#define TSDP_MESSAGE_ADD_HEADER(self, objdef, ...)						\
	{																	\
		tsdp_header_t *header = tsk_object_new(objdef, __VA_ARGS__);	\
		tsdp_message_add_header(self, header);							\
		tsk_object_unref(header);										\
	}
#endif

TINYSDP_API const tsdp_header_t *tsdp_message_get_headerAt(const tsdp_message_t *self, tsdp_header_type_t type, size_t index);
TINYSDP_API const tsdp_header_t *tsdp_message_get_header(const tsdp_message_t *self, tsdp_header_type_t type);
TINYSDP_API const tsdp_header_t *tsdp_message_get_headerByName(const tsdp_message_t *self, char name);

TINYSDP_API int tsdp_message_tostring(const tsdp_message_t *self, tsk_buffer_t *output);


TINYSDP_GEXTERN const void *tsdp_message_def_t;

TSDP_END_DECLS

#endif /* TINYSDP_MESSAGE_H */