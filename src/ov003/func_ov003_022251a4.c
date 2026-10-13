/* func_ov003_022251a4 @ 0x022251a4, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int w[12];
} Big;
typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    char pad_60[4];
    Big unk_64;
} UnkStruct_022251a4;

void func_02055e90(UnkStruct_022251a4 *o, int k);
int func_02065604(void);
void func_02107524(int a, u16 b);

void func_ov003_022251a4(void *self, UnkStruct_022251a4 *o, Big s)
{
    volatile u16 a, b;
    if (o == 0) {
        return;
    }
    o->unk_64 = s;
    func_02055e90(o, 0);
    a = (u16) func_02065604();
    b = a;
    func_02107524(o->unk_5C, b);
}
