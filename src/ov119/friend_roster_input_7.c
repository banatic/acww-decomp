/* friend_roster_input_7: 3 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229c648 @ 0x0229c648, 0xd0 bytes, Thumb
 * func_ov119_0229c608 @ 0x0229c608, 0x3e bytes, Thumb
 * func_ov119_0229c5f4 @ 0x0229c5f4, 0x12 bytes, Thumb
 */

#include "types.h"

// Like func_ov111_022a0a5c: a 16-entry table with two destinations.

typedef struct UnkStruct_0229c648 {
    char pad_00[0x8d];
    u8 unk_8D;
} UnkStruct_0229c648;

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229c608;

extern u16 data_021fbe40[];
extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern int func_020ee45c(UnkStruct_0229c608 *obj);
extern void func_ov090_022993cc(int a, unsigned char b);
extern unsigned char *func_ov002_022080a0(UnkStruct_0229c608 *obj, unsigned char value);
extern void func_ov090_022990c8(int);

int func_ov119_0229c608(UnkStruct_0229c608 *obj, int index);

int func_ov119_0229c648(UnkStruct_0229c648 *o)
{
    int r;
    u16 w;

    func_0206f58c();
    if (func_0206f56c()) {
        switch (o->unk_8D) {
            case 0:
            case 2:
            case 4:
            case 5:
            case 8:
            case 14:
            case 15:
                return func_ov119_0229c608((UnkStruct_0229c608 *) o, 7);
            case 1:
            case 3:
            case 6:
            case 7:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                break;
        }
    }
    if (o->unk_8D != 0 && o->unk_8D != 2) {
        return 0;
    }
    r = -1;
    if (func_0206fe60()) {
        r = func_ov090_022990e0();
    } else {
        w = data_021fbe40[1];
        if (w & 2) {
            r = 7;
        } else if (w & 0x800) {
            r = 0;
        } else if (w & 0x400) {
            r = 5;
        } else if (w & 4) {
            r = 4;
        }
    }
    return func_ov119_0229c608((UnkStruct_0229c608 *) o, r);
}

int func_ov119_0229c608(UnkStruct_0229c608 *obj, int index)
{
    int ret = func_020ee45c(obj);
    if (index != -1 && index != 6) {
        func_ov090_022993cc(ret, (unsigned char) index);
        obj->unk_8C = 3;
        func_ov002_022080a0(obj, 1);
        return 1;
    } else {
        return 0;
    }
}

void func_ov119_0229c5f4(void *arg0)
{
    func_ov090_022990c8((int) func_020ee45c((UnkStruct_0229c608 *) ((void *) arg0)));
}
