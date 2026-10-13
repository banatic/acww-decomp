/* func_02003a90 @ 0x02003a90, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02003a90 {
    u8 pad_00[0x0c];
    void *unk_0C;
    u8 pad_10[0x10];
    u32 unk_20;
    u32 unk_24;
    u8 pad_28[0x8];
    u8 unk_30;
    u8 pad_31;
    u8 unk_32;
};

extern int func_0208a1d0(void *p);
extern int func_0208aef0(struct UnkStruct_02003a90 *p);
extern int func_0208a1b0(void *p, int v);
extern int func_0208aeec(struct UnkStruct_02003a90 *p);
extern int func_0208a198(void *p, int v);
extern void func_02088df8(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l);

void func_02003a90(struct UnkStruct_02003a90 *s)
{
    int r7, r4, r6, r3;
    if (s->unk_24 == 0) {
        return;
    }
    r7 = func_0208a1d0((char *) s + 0xc);
    if (r7 == 0) {
        return;
    }
    r4 = func_0208aef0(s);
    r4 += func_0208a1b0((char *) s + 0xc, -1);
    r6 = func_0208aeec(s);
    r3 = r6 + func_0208a198((char *) s + 0xc, -1);
    if (s->unk_32) {
        r4 += 0x78;
        r3 += 0x48;
    } else {
        r4 += s->unk_20;
        r3 += (s->unk_30 ? 0x8c : 0);
    }
    func_02088df8(0, r7, r4, r3, -1, -1, 0x1000, 0x1000, 0, -1, 0, 0);
}
