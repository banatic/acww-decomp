/* func_ov147_02299b98 @ 0x02299b98, 0x48 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02299b98 {
    int pad_00;
    int unk_04;
} UnkStruct_02299b98;

extern unsigned char data_021c75b8;
extern UnkStruct_02299b98 *func_020682e0(int a);
extern void func_02068320(UnkStruct_02299b98 *p);
extern int func_020b5e10(void);
extern int func_020b6434(int a, int b, int c, int d);
extern void func_020a1888(void);
extern void func_ov147_0229a01c(void *self);

void func_ov147_02299b98(void *self)
{
    unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag > 0) {
        UnkStruct_02299b98 *p = func_020682e0(0);
        if (p->unk_04 == 0) {
            func_02068320(p);
            func_020b6434(func_020b5e10(), 0x2e, 2, 3);
            func_020a1888();
            func_ov147_0229a01c(self);
        }
    }
}
