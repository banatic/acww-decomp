/* fox_tent_4: 4 functions, module ov052
 * mwccarm 1.2/base -O4,s
 * func_ov052_02261a04 @ 0x02261a04, 0x88 bytes, Thumb
 * func_ov052_022619a8 @ 0x022619a8, 0x5c bytes, Thumb
 * func_ov052_022619a0 @ 0x022619a0, 0x8 bytes, Thumb
 * func_ov052_02261998 @ 0x02261998, 0x8 bytes, Thumb
 */

typedef struct {
    char pad_00[0x71e];
    unsigned short unk_71E;
    unsigned short unk_720[3];
} UnkStruct_022619a8;

extern int func_0202edc8(void *self);
extern void func_0201c280(void *a, void *b);
extern void func_ov052_022610d4(void *a, void *b);
extern void MI_CpuFill8(void *s, int c, unsigned int n);
extern void func_0201af28(void *a, int b, int c, int d, int e);
extern unsigned short data_020c80f8;
extern int func_0202ec58(UnkStruct_022619a8 *s);
extern int func_020b65b8(void);
extern int func_02030864(int x);
extern void func_ov052_02261908(UnkStruct_022619a8 *s, int flag);
extern int data_ov052_02261e8c;
extern int data_ov052_02261e5c;

int func_ov052_02261a04(char *self)
{
    if (!func_0202edc8(self)) {
        return 0;
    }
    func_0201c280(self, self + 0x658);
    func_ov052_022610d4(self + 0x658, self);
    *(unsigned short *) (self + 0x71c) = data_020c80f8;
    MI_CpuFill8(self + 0x733, 0, 5);
    MI_CpuFill8(self + 0x738, 0, 5);
    func_0201af28(self + 0x350, 2, 0x400, 0x133, 0x199);
    return 1;
}

int func_ov052_022619a8(UnkStruct_022619a8 *s)
{
    int r;
    int i;

    r = func_0202ec58(s);
    if (r == 0) {
        return 0;
    }
    if (func_020b65b8() != 0) {
        func_ov052_02261908(s, 1);
    } else {
        func_ov052_02261908(s, 0);
    }
    func_02030864(0);
    s->unk_71E = 0xfff1;
    for (i = 0; i < 3; i++) {
        s->unk_720[i] = 0xfff1;
    }
    return 1;
}

int func_ov052_022619a0(void)
{
    return (int) &data_ov052_02261e8c;
}

int func_ov052_02261998(void)
{
    return (int) &data_ov052_02261e5c;
}
