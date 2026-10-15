/* func_ov146_0229a7a4 @ 0x0229a7a4, 0x50 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(int *ptr);
extern int func_ov146_0229a4b0(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char value);
extern int func_ov146_02299670(void *p, int n);
extern void func_ov146_02299650(void *p, int n);
extern void func_ov146_0229a534(void *p);

struct UnkStruct_0229a7a4 {
    char pad_00[0xb2];
    unsigned char flag_b2;
    unsigned char flag_b3;
    char pad_B4[0x15cc - 0xb4];
    int unk_15CC;
};

void func_ov146_0229a7a4(struct UnkStruct_0229a7a4 *p)
{
    if (func_0208e484(&p->unk_15CC) != 0) {
        func_ov146_0229a4b0(p);
        func_ov002_02208098(p, p->flag_b3);
        if (func_ov146_02299670(p, 16) != 0) {
            func_ov146_02299650(p, 16);
            p->flag_b2 = 1;
            func_ov146_0229a534(p);
        }
    }
}
