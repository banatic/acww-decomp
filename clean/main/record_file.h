/* One file of fixed-size records of the ROM (FurnitureRecordFile of furniture_info.h, 0x1c
 * bytes): opened by path with its record size and count, then read either whole into memory
 * (RecordFile_ReadWhole) or eight records at a time into a cache allocated when it is opened.
 * Three of them opened together are record_files.h's. Memory comes from the current heap. */
#ifndef CLEAN_MAIN_RECORD_FILE_H
#define CLEAN_MAIN_RECORD_FILE_H

#include "main/furniture_info.h"

/* The records read into the cache at a time. */
#define RECORD_FILE_CACHE_RECORDS 8

void RecordFile_ReadBlock(FurnitureRecordFile *file, unsigned int index);
char *RecordFile_Record(FurnitureRecordFile *file, unsigned int index);
void RecordFile_Close(FurnitureRecordFile *file);
void RecordFile_FreeWhole(FurnitureRecordFile *file);
void RecordFile_ReadWhole(FurnitureRecordFile *file);
int RecordFile_Open(FurnitureRecordFile *file, const char *path, int record_size, int records);
int RecordFile_Destruct(FurnitureRecordFile *file);
void RecordFile_Construct(FurnitureRecordFile *file);

#endif
