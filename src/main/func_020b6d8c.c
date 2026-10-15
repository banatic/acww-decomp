/* func_020b6d8c @ 0x020b6d8c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020b0b00_2 UnkStruct_020b0b00_2;

extern int func_020b0abc(UnkStruct_020b0b00_2 **ptr, u8 *cnt, u8 *flag, u64 start);
extern UnkStruct_020b0b00_2 **data_021f6948;
extern u8 data_021f42dc;
extern u8 data_021f42e4;

void func_020b6d8c(int unused, u64 start)
{
    func_020b0abc(data_021f6948, &data_021f42dc, &data_021f42e4, start);
}
