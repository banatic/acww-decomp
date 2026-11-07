/* Three files of fixed-size records opened together (RecordFiles of furniture_info.h):
 * the furniture's (data_021c8c48: "/ftr_info/always.bin", "indoor.bin", "dma.bin") and the
 * items' (item_info.h) are each one of these. The first file is read whole when they are opened;
 * the second can be read whole on request and freed again; records are read through each file's
 * own functions (main, func_0206e778 and on). */
#ifndef CLEAN_MAIN_RECORD_FILES_H
#define CLEAN_MAIN_RECORD_FILES_H

#include "main/furniture_info.h"

int RecordFiles_Third(int files);
int RecordFiles_Second(int files);
RecordFile *RecordFiles_First(RecordFiles *files);
int RecordFiles_FreeSecond(RecordFiles *files);
int RecordFiles_LoadSecond(RecordFiles *files, int stream);
void RecordFiles_Close(RecordFiles *files);
int RecordFiles_Open(RecordFiles *files, const char *path0, int size0, const char *path1, int size1, const char *path2,
                     int size2, int records);

#endif
