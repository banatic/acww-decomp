/* func_02054ed4 @ 0x02054ed4, 0x92 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    void *unk_00; // 0x0
    char pad_04[0xb0];
    void *t; // 0xb4
} UnkStruct_02054ed4;

extern void func_02070d24(u8 b);
extern void func_02070c50(void *a, void *b, int c);
extern void func_02070cc4(void *a);
extern void func_02070ca4(void *a);
extern void func_02070cf4(void *a, void *b);
extern void func_02070d4c(u8 b);

void func_02054ed4(void *unused, UnkStruct_02054ed4 *s, int p2)
{
    int r4;
    int v;

    r4 = *(unsigned char *) s->unk_00 & 0xe0;
    if (r4 == 0x40) {
        func_02070d24(((u8 *) s->unk_00)[4]);
    } else if (r4 == 0x60) {
        func_02070d24(((u8 *) s->unk_00)[5]);
    }

    if (p2 != 0) {
        func_02070c50((char *) s->t + 0x28, (char *) s->t + 0x4c, p2);
    } else {
        v = *(int *) s->t;
        if (v & 2) {
            if (!(v & 4)) {
                func_02070cc4((char *) s->t + 0x4c);
            }
        } else {
            if (v & 4) {
                func_02070ca4((char *) s->t + 0x28);
            } else {
                func_02070cf4((char *) s->t + 0x28, (char *) s->t + 0x4c);
            }
        }
    }

    if (r4 == 0x20 || r4 == 0x60) {
        func_02070d4c(((u8 *) s->unk_00)[4]);
    }
}
