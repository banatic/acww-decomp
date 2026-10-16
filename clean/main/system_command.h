/* The command list of system packet kind 13 (SystemPacket_RunCommands): a run of sections, each
 * a 3-byte header (the data's length, 2 bytes little-endian, and an opcode) and its data.
 *
 * SystemCommand_BuildList builds one in the share block, calling the section writer of each
 * opcode (data_020ccf98) and leaving out a section it wrote nothing into; the caller sends it
 * with SystemPacket_SendShareData. On the receiving system SystemCommand_RunList hands each
 * section to the handler of its opcode (data_020ccfa0).
 *
 * Two opcodes exist. Opcode 0 has an empty writer and handler (SystemCommand_WriteNothing,
 * SystemCommand_ReadNothing). Opcode 1 carries the eight entries of data_021d13e4
 * (func_0207b9d0), 19 bytes each: written by SystemCommand_WriteEntries and read back by
 * SystemCommand_ReadEntries. */
#ifndef CLEAN_MAIN_SYSTEM_COMMAND_H
#define CLEAN_MAIN_SYSTEM_COMMAND_H

#include "types.h"

#define SYSTEM_COMMAND_OPCODES 2
#define SYSTEM_COMMAND_HEADER_SIZE 3

/* A section's handler: its data and the data's length. */
typedef void SystemCommandHandler(u8 *data, u16 length);
/* A section's writer: appends the section's data to the share block. */
typedef void SystemCommandWriter(int slot);

void SystemCommand_RunList(u8 *list, u32 length);
int SystemCommand_BuildList(int slot);
void SystemCommand_ReadEntries(u8 *data, u16 length);
void SystemCommand_ReadNothing(u8 *data, u16 length);
void SystemCommand_WriteEntries(int slot);
void SystemCommand_WriteNothing(int slot);

#endif
