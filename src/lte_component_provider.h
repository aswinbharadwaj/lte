/*
 * lte_component_provider.h
 *
 *  Created on: 08-Apr-2013
 *      Author: aswin
 */



/*
 * Lte lttng-ust tracepoint provider.
 */


/*
 * Here, "lte" is the project, and "component" is the
 * component.
 */

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER lte_component


 /* include file (this files's name)*/

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "/home/aswin/Documents/project/Lte/src/lte_component_provider.h"


/*
 * Macro and its matching element to make sure the program
 * works in c++.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * Precompiler conditionals to ensure the tracepoint event generation
 * can include this file more than once.
 */

#if !defined(_LTE_COMPONENT_PROVIDER_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _LTE_COMPONENT_PROVIDER_H

/*
 * To allow programs to call "tracepoint(...):
 */

#include <lttng/tracepoint.h>

/*
 * Tracepoint event that writes the packet content into the
 * field message of the trace event message in the provider
 */

		TRACEPOINT_EVENT(
			/*
			 * provider name i.e. TRACEPOINT_PROVIDER
			 */
			lte_component,
			/*
			 * tracepoint name
			 */
			udp_packet,
			/*
			 * TP_ARGS macro contains the arguments passed for the tracepoint
			 */
			TP_ARGS(char*, layer, int, index, char *, payload, int, size),
			/*
			 * TP_FIELDS describes how to write the fields of the trace event.
			 */
			TP_FIELDS(
				ctf_string(layer, layer)
				ctf_integer(int, index, index)
				ctf_string(payload, payload)
				ctf_integer(int, size, size)
			)
		)
		TRACEPOINT_EVENT(
			lte_component,

			pdcp_packet,

			TP_ARGS(char*, layer, int, userid, char *, payload, int, type, char*, encrypted_data),

			TP_FIELDS(
				ctf_string(layer, layer)
				ctf_integer(int, userid, userid)
				ctf_string(payload, payload)
				ctf_integer(int, type, type)
				ctf_string(encrypted_data, encrypted_data)
			)
	   )
	   TRACEPOINT_EVENT(

		   lte_component,

		   rlc_packet,

		   TP_ARGS(char *, layer, int, userid, int, sequence_number, char*, content),

		   TP_FIELDS(

			ctf_string(layer, layer)
			ctf_integer(int, userid, userid)
			ctf_integer(int, sequence_number, sequence_number)
			ctf_string(content, content)
		   )
	  )

/*
 * Trace loglevel, shows the level of the trace event. It can be TRACE_EMERG,
 * TRACE_ALERT, TRACE_CRIT, TRACE_ERR, TRACE_WARNING, TRACE_INFO or others.
 * If this is not set, TRACE_DEFAULT is assumed.
 */
TRACEPOINT_LOGLEVEL(
       /*
        * The provider name, same as the provider name in the
        * TRACEPOINT_EVENT and as TRACEPOINT_PROVIDER above.
        */
	lte_component,
       /*
        * The tracepoint name, msame as the tracepoint name in the
        * TRACEPOINT_EVENT
        */
	packet,
       /*
        * The tracepoint loglevel
        */
	TRACE_WARNING)

#endif /* _LTE_COMPONENT_PROVIDER_H */

/*
 * Adding this after defining the tracepoint events to expand the macros.
 */

#include <lttng/tracepoint-event.h>

/*
 * Macro and its matching element to make sure the program
 * works in c++.
 */
#ifdef __cplusplus
}
#endif /* __cplusplus */

