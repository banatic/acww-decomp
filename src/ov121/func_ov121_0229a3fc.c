/* func_ov121_0229a3fc @ 0x0229a3fc, 0x54 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229a3fc {
    int pad_00;
} UnkStruct_0229a3fc;

typedef struct UnkStruct_0229a3fc_2 {
    unsigned char pad_00[0x3a8];
    UnkStruct_0229a3fc sub;
} UnkStruct_0229a3fc_2;

extern int func_ov121_0229a3a8(UnkStruct_0229a3fc_2 *p);
extern int func_ov121_0229a37c(UnkStruct_0229a3fc_2 *p);
extern int func_ov121_02299fc8(UnkStruct_0229a3fc_2 *p);
extern void func_ov121_0229a190(UnkStruct_0229a3fc_2 *p);
extern void func_ov002_0220a0b4(UnkStruct_0229a3fc *addr, int a, int b);
extern void func_ov002_0220a374(UnkStruct_0229a3fc *addr, int val);

void func_ov121_0229a3fc(UnkStruct_0229a3fc_2 *p)
{
    int r4;
    int r2;
    int ret;
    r4 = func_ov121_0229a3a8(p);
    r2 = func_ov121_0229a37c(p);
    func_ov002_0220a0b4(&p->sub, r4, r2);
    ret = func_ov121_02299fc8(p);
    if (ret != -1) {
        func_ov002_0220a374(&p->sub, 13);
    } else {
        func_ov002_0220a374(&p->sub, 1);
    }
    func_ov121_0229a190(p);
}
