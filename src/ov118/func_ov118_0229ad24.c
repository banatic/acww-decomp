/* func_ov118_0229ad24 @ 0x0229ad24, 0xb0 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229b374(void *arg0);
extern void func_ov118_0229a440(void *obj, int arg);
extern int _s32_div_f(int a, int b);

struct UnkStruct_0229ad24 {
    char pad_00[0x98];
    unsigned short unk_98;
    unsigned short unk_9A;
    char pad_9C[0xa4 - 0x9c];
    unsigned char unk_A4;
};

void func_ov118_0229ad24(struct UnkStruct_0229ad24 *obj)
{
    int r4 = func_ov118_0229b374((void *) obj);

    if (r4 == 0) {
        func_ov118_0229a440(obj, 0x10);
        obj->unk_A4 = 0;
        return;
    }

    if (obj->unk_98 == obj->unk_9A) {
        func_ov118_0229a440(obj, 0x10);
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
