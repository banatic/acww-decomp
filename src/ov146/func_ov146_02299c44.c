/* func_ov146_02299c44 @ 0x02299c44, 0x78 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e895c(void *p, int v, int n);
extern void func_ov002_0220a4c8(void *p);
extern void func_ov146_02299b1c(void *p);
extern void func_ov146_02299b58(void *p);

typedef struct {
    char pad_00[0x98];
    int unk_98;
    int unk_9C;
    int unk_A0;
    char pad_A4[0x1fb4 - 0xa4];
    char unk_1FB4;
} UnkStruct_02299c44;

void func_ov146_02299c44(UnkStruct_02299c44 *obj, int param2, int param3)
{
    if (param3 != 0) {
        param2 -= 0x40;
    } else {
        param2 += obj->unk_9C;
    }

    if (param2 < 0) {
        param2 = 0;
    }
    if (param2 > 0x50) {
        param2 = 0x50;
    }

    if (param3 != 0) {
        func_020e895c(&obj->unk_98, param2, 8);
    } else {
        obj->unk_98 = param2;
    }

    func_ov146_02299b1c(obj);
    func_ov146_02299b58(obj);

    {
        int diff = obj->unk_A0 - obj->unk_98;

        if (diff < 4) {
            if (diff > -4) {
                return;
            }
        }

        func_ov002_0220a4c8(&obj->unk_1FB4);
        obj->unk_A0 = obj->unk_98;
    }
}
