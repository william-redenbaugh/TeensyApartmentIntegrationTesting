/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.2-dev */

#ifndef PB_EMBEDDEDMESSAGES_MESSAGEDATA_PB_H_INCLUDED
#define PB_EMBEDDEDMESSAGES_MESSAGEDATA_PB_H_INCLUDED
#include "pb.h"

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _MessageData_MessageType {
    MessageData_MessageType_GENERAL_INSTRUCTIONS = 0,
    MessageData_MessageType_MATRIX_DATA = 1,
    MessageData_MessageType_LED_STRIP_DATA = 2
} MessageData_MessageType;

/* Struct definitions */
typedef struct _MessageData {
    uint32_t message_size;
    MessageData_MessageType message_type;
} MessageData;


/* Helper constants for enums */
#define _MessageData_MessageType_MIN MessageData_MessageType_GENERAL_INSTRUCTIONS
#define _MessageData_MessageType_MAX MessageData_MessageType_LED_STRIP_DATA
#define _MessageData_MessageType_ARRAYSIZE ((MessageData_MessageType)(MessageData_MessageType_LED_STRIP_DATA+1))


/* Initializer values for message structs */
#define MessageData_init_default                 {0, _MessageData_MessageType_MIN}
#define MessageData_init_zero                    {0, _MessageData_MessageType_MIN}

/* Field tags (for use in manual encoding/decoding) */
#define MessageData_message_size_tag             1
#define MessageData_message_type_tag             2

/* Struct field encoding specification for nanopb */
#define MessageData_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   message_size,      1) \
X(a, STATIC,   SINGULAR, UENUM,    message_type,      2)
#define MessageData_CALLBACK NULL
#define MessageData_DEFAULT NULL

extern const pb_msgdesc_t MessageData_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define MessageData_fields &MessageData_msg

/* Maximum encoded size of messages (where known) */
#define MessageData_size                         8

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
