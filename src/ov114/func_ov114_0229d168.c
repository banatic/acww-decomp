/* func_ov114_0229d168 @ 0x0229d168, 0x74 bytes, Thumb, module ov114
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d168 {
    char pad_00[0x127c];
    int unk_127C;
    int unk_1280;
} UnkStruct_0229d168;

extern void func_ov114_0229d500(UnkStruct_0229d168 *p);
extern int func_ov114_0229cb7c(UnkStruct_0229d168 *p, int value);
extern void func_ov114_0229cadc(UnkStruct_0229d168 *p);

void func_ov114_0229d168(UnkStruct_0229d168 *p)
{
    int acc = p->unk_127C;
    int val = p->unk_1280;

    if (val > 0) {
        if (val < 0xb) {
            acc += val;
            p->unk_1280 = 0;
        } else {
            acc += 0xb;
            p->unk_1280 = val - 0xb;
        }
    } else if (val < 0) {
        if (val > -11) {
            acc += val;
            p->unk_1280 = 0;
        } else {
            acc -= 0xb;
            p->unk_1280 = val + 0xb;
        }
    }

    if (acc != p->unk_127C) {
        func_ov114_0229d500(p);
        if (func_ov114_0229cb7c(p, acc) != 0) {
            func_ov114_0229cadc(p);
        }
    }
}
