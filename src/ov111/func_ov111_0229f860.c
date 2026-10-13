/* func_ov111_0229f860 @ 0x0229f860, 0xcc bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0229f860 {
    u8 pad_00[0x9e];
    u8 unk_9E;
    u8 unk_9F;
    u8 unk_A0;
    u8 pad_A1[0xac - 0xa1];
    u8 pad_AC[0x3eb8 - 0xac];
    u16 arr_3eb8[1];
} UnkStruct_0229f860;

extern int func_ov111_0229efd8(UnkStruct_0229f860 *s, int v);
extern void func_ov095_0229b394(void *p);
extern int func_ov111_0229f4dc(UnkStruct_0229f860 *s);
extern u8 func_ov095_0229bbc0(void *a, void *b, u8 c, u8 d, int e);
extern int func_ov111_0229efb8(UnkStruct_0229f860 *s, int v);
extern void func_ov095_0229b3ec(void *p);
extern int func_02051c8c_unk(u16 *arr, int size);
extern int func_ov095_0229bcec(void *a, void *b, u16 c, void *d, int e, int f, int g, int h);
extern void func_ov111_0229f854(UnkStruct_0229f860 *s);
extern void func_ov111_0229f524(UnkStruct_0229f860 *s);
extern void func_ov111_0229fd08(UnkStruct_0229f860 *s);
extern void func_ov095_022999e8(void *p);
extern void func_ov095_0229b388(void *p);

void func_ov111_0229f860(UnkStruct_0229f860 *s)
{
    int n;
    int i;
    int z;

    if (func_ov111_0229efd8(s, 8) == 0) {
        return;
    }

    func_ov095_0229b394((char *) s + 0xac);

    if (func_ov111_0229f4dc(s) != 0) {
        s->unk_9E = func_ov095_0229bbc0((char *) s + 0xac, (char *) s + 0x3d16, s->unk_9F, s->unk_A0, 0x10);
        func_ov111_0229efb8(s, 1);
    }

    func_ov095_0229b3ec((char *) s + 0xac);

    n = func_02051c8c_unk(s->arr_3eb8, 0x10);
    i = 0;
    z = i;

    while (i < n) {
        if (func_ov095_0229bcec((char *) s + 0xac, (char *) s + 0x3d16, s->arr_3eb8[i], &s->unk_9E, 0x10, 0xa0, z, z) == 0) {
            if (i == 0) {
                func_ov111_0229f854(s);
            }
            i = n;
        }
        i++;
    }

    func_ov111_0229f524(s);
    func_ov111_0229fd08(s);
    func_ov095_022999e8((char *) s + 0xac);
    s = (UnkStruct_0229f860 *) ((char *) s + 0xac);
    func_ov095_0229b388(s);
}
