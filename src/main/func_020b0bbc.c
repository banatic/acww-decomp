/* func_020b0bbc @ 0x020b0bbc, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u16 a;
    u16 b;
} UnkStruct_020b0bbc;
typedef struct {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[2];
    UnkStruct_020b0bbc *e;
} UnkStruct_020b0bbc_2;

extern int data_021f42f4;
extern void func_0202f134(int a, int b, int c, int d);
extern u64 OS_GetTick(void);

int func_020b0bbc(UnkStruct_020b0bbc_2 *self, u8 *cnt, u64 start)
{
    unsigned int ok;
    u8 i;
    UnkStruct_020b0bbc *e;

    if (cnt != 0) {
        i = *cnt;
    } else {
        i = 0;
    }
    e = self->e + i;
    ok = 1;
    for (;;) {
        func_0202f134(e->a, data_021f42f4, e->b, 0);
        e++;
        i = (u8) (i + 1);
        if (cnt != 0) {
            *cnt = (u8) (*cnt + 1);
        }
        if (i >= self->unk_01) {
            break;
        }
        if (cnt != 0) {
            if ((unsigned int) ((OS_GetTick() - start) * 64 / 33514) > 0x28) {
                ok = 0;
                break;
            }
        }
    }
    if (ok != 0) {
        return 1;
    }
    return 0;
}
