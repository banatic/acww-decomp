/* The last four bytes of the state block (0x173f8, StateBlock.part_173f8, data_021f3ba0),
 * written to the card with it:
 *
 *   a checksum that makes the block's 16-bit halfword sum come out right (func_020a1f4c);
 *   a status: SAVE_STAMP_WRITING (28) is set before the activity process writes the copies of the
 *   block to the card and SAVE_STAMP_WRITTEN (2) once they are written; a new town is
 *   marked written too (StateBlock_SetUpTown), and StateBlock_IsSetUp needs it;
 *   a serial: a random number given to a new save (SaveStamp_NewSerial), which two copies on
 *   the card share when they are of the same save (func_020a16e0). */
#ifndef CLEAN_MAIN_SAVE_STAMP_H
#define CLEAN_MAIN_SAVE_STAMP_H

#include "types.h"

enum SaveStampStatus {
    SAVE_STAMP_NONE = 0,
    SAVE_STAMP_WRITTEN = 2,
    SAVE_STAMP_WRITING = 28,
};

typedef struct SaveStamp {
    u16 checksum;
    u8 status; /* SaveStampStatus */
    u8 serial;
} SaveStamp;

int SaveStamp_Checksum(SaveStamp *stamp);
void SaveStamp_SetChecksum(SaveStamp *stamp, int checksum);
int SaveStamp_Serial(SaveStamp *stamp);
void SaveStamp_SetSerial(SaveStamp *stamp, int serial);
void SaveStamp_NewSerial(SaveStamp *stamp);
int SaveStamp_HasNoWrite(const SaveStamp *stamp);
int SaveStamp_IsWritten(SaveStamp *stamp);
void SaveStamp_MarkWritten(SaveStamp *stamp);
void SaveStamp_MarkWriting(SaveStamp *stamp);
void SaveStamp_Clear(SaveStamp *stamp);
void SaveStamp_MarkTownWritten(SaveStamp *stamp);
void SaveStamp_Destruct(SaveStamp *stamp);
void SaveStamp_Construct(SaveStamp *stamp);
void SaveStamp_SetLostFlag(char value);

#endif
