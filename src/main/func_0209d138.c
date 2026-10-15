/* func_0209d138 @ 0x0209d138, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0209d138_2 {
    char data[0x1c];
};

typedef struct {
    u16 unk_00;
    u32 unk_04;
    u32 unk_08;
    struct UnkStruct_0209d138_2 *arr;
    u32 unk_10;
    void (*unk_14)(void);
} UnkStruct_0209d138;

extern int func_0209d2d0(struct UnkStruct_0209d138_2 *p);
extern void func_020e9898(struct UnkStruct_0209d138_2 *p);

int func_0209d138(UnkStruct_0209d138 *s)
{
    if (s->arr != 0) {
        struct UnkStruct_0209d138_2 *p = s->arr;
        u32 i;

        for (i = 0; i < s->unk_04; i++) {
            func_0209d2d0(p);
            p++;
        }

        func_020e9898(s->arr);
    }

    if (s->unk_14 != 0) {
        s->unk_14();
    }

    s->unk_10 = 0;
    s->unk_14 = 0;
    s->unk_04 = 0;
    s->unk_08 = 0;
    s->unk_00 = 0xffff;
    s->arr = 0;

    return 1;
}
