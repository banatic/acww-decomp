/* func_020b0b00 @ 0x020b0b00, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 unk_00;
    u8 pad[7];
} UnkStruct_020b0b00;
typedef struct {
    u16 unk_00;
    u16 pad;
    UnkStruct_020b0b00 *e;
} UnkStruct_020b0b00_2;
typedef int (*Fn)(UnkStruct_020b0b00 *e, u8 *flag, u64 t);

extern Fn data_020e41ec[];
extern u64 OS_GetTick(void);

int func_020b0b00(UnkStruct_020b0b00_2 *self, u8 *cnt, u8 *flag, u64 start)
{
    unsigned int ok;
    int ret;
    int i;
    UnkStruct_020b0b00 *e;
    Fn fn;

    if (cnt != 0) {
        i = *cnt;
    } else {
        i = 0;
    }
    e = self->e + i;
    ok = 1;
    while (i < (int) self->unk_00) {
        ret = ok;
        fn = data_020e41ec[e->unk_00];
        if (fn != 0) {
            ret = fn(e, flag, start);
        }
        if (ret != 0) {
            e++;
            i++;
            if (flag != 0) {
                *flag = 0;
            }
            if (cnt != 0) {
                *cnt = (u8) (*cnt + 1);
            }
            if (i >= (int) self->unk_00) {
                break;
            }
            if (cnt != 0) {
                if ((u32) ((OS_GetTick() - start) * 64 / 33514) > 0x28) {
                    ok = 0;
                    break;
                }
            }
            continue;
        }
        ok = 0;
        break;
    }
    if (ok != 0) {
        return 1;
    }
    return 0;
}
