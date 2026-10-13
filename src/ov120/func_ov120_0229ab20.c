/* func_ov120_0229ab20 @ 0x0229ab20, 0xb0 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229b14c(void *obj);
extern void func_ov120_0229a428(void *obj, int arg);
extern int _s32_div_f(int a, int b);

struct UnkStruct_0229ab20 {
    char pad_00[0x98];
    unsigned short unk_98;
    unsigned short unk_9A;
    char pad_9C[0xa4 - 0x9c];
    unsigned char unk_A4;
};

void func_ov120_0229ab20(struct UnkStruct_0229ab20 *obj)
{
    int r4 = func_ov120_0229b14c(obj);

    if (r4 == 0) {
        func_ov120_0229a428(obj, 0x10);
        obj->unk_A4 = 0;
        return;
    }

    if (obj->unk_98 == obj->unk_9A) {
        func_ov120_0229a428(obj, 0x10);
    } else if (obj->unk_98 < obj->unk_9A) {
        obj->unk_98 += 8;
        if (obj->unk_98 > obj->unk_9A) {
            obj->unk_98 = obj->unk_9A;
        }
    } else if (obj->unk_98 < 8) {
        obj->unk_98 = obj->unk_9A;
    } else {
        obj->unk_98 -= 8;
        if (obj->unk_98 < obj->unk_9A) {
            obj->unk_98 = obj->unk_9A;
        }
    }

    obj->unk_A4 = (unsigned char) _s32_div_f(obj->unk_98 * 0x58, r4);
}
