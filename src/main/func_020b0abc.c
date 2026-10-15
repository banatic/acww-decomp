/* func_020b0abc @ 0x020b0abc, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020b0b00_2 UnkStruct_020b0b00_2;

extern int func_020b0b00(UnkStruct_020b0b00_2 *self, u8 *cnt, u8 *flag, u64 start);

int func_020b0abc(UnkStruct_020b0b00_2 **ptr, u8 *cnt, u8 *flag, u64 start)
{
    return func_020b0b00(*ptr, cnt, flag, start);
}
