/* func_ov055_02260544 @ 0x02260544, 0x5c bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b1130(void);
extern int func_02090040(int a);
extern void MI_CpuCopy8(int a, void *b, int c);
extern void func_02090174(int a);
extern int func_020a145c(void);

typedef struct {
    unsigned char pad_00[0x710];
    unsigned char unk_710;
    unsigned char pad_711[3];
    unsigned char unk_714[0x23C];
    unsigned char pad_950[0x818];
    unsigned char unk_1168;
} UnkStruct_02260544;

void func_ov055_02260544(UnkStruct_02260544 *p)
{
    int r;
    func_020b1130();
    r = func_02090040(4);
    MI_CpuCopy8(r, p->unk_714, 0x950);
    p->unk_1168 = 1;
    func_02090174(r);
    if (p->unk_710 == 0) {
        int t = func_020a145c();
        if (t == 1 || t == 4) {
            p->unk_710 = 1;
        }
    }
}
