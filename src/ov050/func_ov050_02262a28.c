/* func_ov050_02262a28 @ 0x02262a28, 0x90 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209ad9c(void *p, int q);
extern int func_0209b4d4(int x);
extern int func_0209bd44(int x);
extern int func_0209bc40(int x);
extern void func_0209bb90(int x, int y);
extern int func_02099fe8(void);
extern void func_02094fd4(void *p);
extern void func_0209ab34(void *p);
extern void func_0209ac50(void *p, void *q, void *r);
extern void func_02068404(int a, int b, void *c);
extern void func_02094fbc(void *p);

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0x70];
    void *unk_B4;
    char pad_B8[0x18];
    int unk_D0;
} UnkStruct_02262a28;

void func_ov050_02262a28(UnkStruct_02262a28 *a, void *p1)
{
    short w;
    int local2[9];
    int ret;

    ret = func_0209b4d4(func_0209ad9c(p1, 0));
    if (func_0209bd44(ret) != 0) {
        if (func_0209bc40(ret) == 0xd) {
            func_0209bb90(ret, 1);
        }
    }
    if (func_02099fe8() >= 0) {
        func_02094fd4(local2);
        func_0209ab34(p1);
        w = 0x1563;
        func_0209ac50(p1, local2, &w);
        func_02068404(a->unk_40, 1, local2);
        ((char *) a->unk_B4)[0x73e] = 0;
        a->unk_D0 = 0x18;
        func_02094fbc(local2);
    } else {
        a->unk_D0 = 0x17;
    }
}
