/* Main's code at 020ba298 (block_020ba298.h). */
#include "block_020ba298.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "player_record.h"
#include "player_records.h"

extern const u32 data_020e69a4[]; /* the class's vtable */
extern const u32 data_020da13c[]; /* the base class's (Process) */

extern u8 data_021fba68[];
extern u8 data_021f8b48[];
extern void func_020bc514(void *object);

/* The flag Block020ba298_SetPlayerFlag32 sets. */
#define BLOCK_020BA298_PLAYER_FLAG 0x32

/* func_020ba298: the destructor. */
Process *Block020ba298_Destruct(Process *process)
{
    process->vtable = data_020e69a4;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    return process;
}
CLEAN_AS(func_020ba298, Block020ba298_Destruct)

/* func_020ba2b8: the destructor, then the object freed. */
Process *Block020ba298_DestructFree(Process *process)
{
    process->vtable = data_020e69a4;
    process->vtable = data_020da13c;
    Process_Destruct(process);
    Heap_FreeAux(process);
    return process;
}
CLEAN_AS(func_020ba2b8, Block020ba298_DestructFree)

/* func_020ba2e0 */
void Block020ba298_SetByte9(void)
{
    data_021fba68[9] = 1;
}
CLEAN_AS(func_020ba2e0, Block020ba298_SetByte9)

/* func_020ba2ec: when there is a player at this console, its flag 0x32 set and func_020bc514
 * run on data_021f8b48. */
void Block020ba298_SetPlayerFlag32(void)
{
    u8 *record = PlayerRecords_Current();
    if (record != NULL) {
        PlayerRecord_SetFlag(record, BLOCK_020BA298_PLAYER_FLAG);
        func_020bc514(data_021f8b48);
    }
}
CLEAN_AS(func_020ba2ec, Block020ba298_SetPlayerFlag32)
