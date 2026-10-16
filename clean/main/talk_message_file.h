/* The message file of a talk (class data_020def64, 0x8a4 bytes, the talk's member at 0xb14,
 * talk_object.h): a message file of the "MESGbmg1" format (bmg_file.h, built with entries of
 * 0x0c bytes) with a buffer of 0x800 bytes at 0xa4 that a message is read into. Its vtable has
 * the destructor, the deleting destructor, the buffer's address and its size. */
#ifndef CLEAN_MAIN_TALK_MESSAGE_FILE_H
#define CLEAN_MAIN_TALK_MESSAGE_FILE_H

#include "bmg_file.h"
#include "types.h"

#define TALK_MESSAGE_FILE_BUFFER_SIZE 0x800

typedef struct TalkMessageFile {
    BmgFile base;                             /* 0x000 */
    u8 buffer[TALK_MESSAGE_FILE_BUFFER_SIZE]; /* 0x0a4 */
} TalkMessageFile;

int TalkMessageFile_Size(void);
int TalkMessageFile_Buffer(int file);
void TalkMessageFile_Clear(TalkMessageFile *file);
TalkMessageFile *TalkMessageFile_Delete(TalkMessageFile *file);
TalkMessageFile *TalkMessageFile_Destruct(TalkMessageFile *file);
TalkMessageFile *TalkMessageFile_Construct(TalkMessageFile *file);

#endif
