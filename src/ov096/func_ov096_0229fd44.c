/* func_ov096_0229fd44 @ 0x0229fd44, 0x6a bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xB6];
    unsigned char unk_B6;
    char pad_B7[0x0A];
    volatile unsigned char unk_C1;
} UnkStruct_0229fd44;

extern void func_ov002_02208098(UnkStruct_0229fd44 *p, int arg);
extern void func_ov096_0229ec90(UnkStruct_0229fd44 *p, unsigned char b);
extern void func_ov096_0229ed44(UnkStruct_0229fd44 *p);
extern void func_ov096_0229f5ac(UnkStruct_0229fd44 *p, unsigned char b);
extern void func_ov096_0229fdf8(UnkStruct_0229fd44 *p);

void func_ov096_0229fd44(UnkStruct_0229fd44 *p)
{
    int rem;
    if (p->unk_C1 != 0) {
        p->unk_C1 = p->unk_C1 - 1;
        rem = p->unk_C1 % 5;
        if (rem != 0) {
            if (rem == 3) {
                func_ov096_0229ec90(p, p->unk_B6);
            }
        } else {
            func_ov096_0229ed44(p);
        }
        if (p->unk_C1 == 0) {
            func_ov096_0229f5ac(p, p->unk_B6);
        }
    } else {
        func_ov002_02208098(p, 0x2f);
        func_ov096_0229fdf8(p);
    }
}
