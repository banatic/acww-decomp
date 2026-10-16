/* The message reader's message file and three text classes of main.
 *
 * - The message file (vtable data_020e51e8, 0xaa4 bytes, the reader's member at 0x4c): a file
 *   (the base class of data_020e3d34, func_020a9a90 builds it) with a buffer of 0xa00 bytes at
 *   0xa4 that a message is read into. Its vtable has the destructor, the deleting destructor,
 *   the buffer's address and its size.
 * - Three texts derived from the label base of text_label.h (built by func_020a8cac, destroyed
 *   by func_020a8c38), whose characters start at 0x12. Their vtables have the destructor, the
 *   deleting destructor, the capacity in characters and the characters' address:
 *     data_020e51b8   10 characters, 0x20 bytes (the reader's 16 items; ends with a 0 byte)
 *     data_020e5218   46 characters, 0x40 bytes (number_text.h formats numbers into one)
 *     data_020e51d0  256 characters, 0x118 bytes (one is a global object, MessageText256_Global,
 *                    that the forbidden-word filter copies the text it filters into) */
#ifndef CLEAN_MAIN_MESSAGE_TEXTS_H
#define CLEAN_MAIN_MESSAGE_TEXTS_H

#include "types.h"

#define MESSAGE_FILE_BUFFER_SIZE 0xa00
#define MESSAGE_TEXT_START 0x12
#define MESSAGE_TEXT10_CAPACITY 10
#define MESSAGE_TEXT46_CAPACITY 46
#define MESSAGE_TEXT256_CAPACITY 256

typedef struct MessageFile {
    const void *vtable;
    u8 base_04[0xa0];                    /* the file base's */
    u8 buffer[MESSAGE_FILE_BUFFER_SIZE]; /* 0xa4 */
} MessageFile;

typedef struct MessageText10 {
    const void *vtable;
    u8 base_04[MESSAGE_TEXT_START - 4]; /* the label base's */
    char text[MESSAGE_TEXT10_CAPACITY]; /* 0x12 */
    u8 end;                             /* 0x1c: 0, after the characters */
    u8 unk_1d[3];
} MessageText10;

typedef struct MessageText46 {
    const void *vtable;
    u8 base_04[MESSAGE_TEXT_START - 4];
    char text[MESSAGE_TEXT46_CAPACITY]; /* 0x12 */
} MessageText46;

typedef struct MessageText256 {
    const void *vtable;
    u8 base_04[MESSAGE_TEXT_START - 4];
    char text[MESSAGE_TEXT256_CAPACITY]; /* 0x12 */
    u8 unk_112[6];
} MessageText256;

int MessageFile_Size(void);
int MessageFile_Buffer(int file);
void MessageFile_Clear(MessageFile *file);
MessageFile *MessageFile_Delete(MessageFile *file);
MessageFile *MessageFile_Destruct(MessageFile *file);
MessageFile *MessageFile_Construct(MessageFile *file);

int MessageText10_Buffer(int text);
int MessageText10_Capacity(void);
MessageText10 *MessageText10_Delete(MessageText10 *text);
MessageText10 *MessageText10_Destruct(MessageText10 *text);
MessageText10 *MessageText10_Construct(MessageText10 *text);

MessageText256 *MessageText256_Global(void);
int MessageText256_Buffer(int text);
int MessageText256_Capacity(void);
MessageText256 *MessageText256_Delete(MessageText256 *text);
MessageText256 *MessageText256_Destruct(MessageText256 *text);
MessageText256 *MessageText256_Construct(MessageText256 *text);

int MessageText46_Buffer(int text);
int MessageText46_Capacity(void);
MessageText46 *MessageText46_Delete(MessageText46 *text);
MessageText46 *MessageText46_Destruct(MessageText46 *text);
MessageText46 *MessageText46_Construct(MessageText46 *text);

#endif
