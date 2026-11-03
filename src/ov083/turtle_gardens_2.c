/* turtle_gardens_2: 6 functions, module ov083
 * mwccarm 1.2/base -O4,s
 * func_ov083_02278e64 @ 0x02278e64, 0x34 bytes, Thumb
 * func_ov083_02278e18 @ 0x02278e18, 0x4c bytes, Thumb
 * func_ov083_02278e08 @ 0x02278e08, 0xe bytes, Thumb
 * func_ov083_02278dd0 @ 0x02278dd0, 0x38 bytes, Thumb
 * func_ov083_02278da4 @ 0x02278da4, 0x2c bytes, Thumb
 * func_ov083_02278da0 @ 0x02278da0, 0x4 bytes, Thumb
 */

struct ov083_02278da4_struct {
    char pad_00[0x618];
    char unk_618;
};

extern unsigned short data_020c80f8;
extern int func_02019d0c(char *ptr, int kind, int value, int r3val, int argA, short argB, short argC, int argD, int argE,
                         unsigned short argF, unsigned short argG);
extern void func_020861dc(void *a);
extern void func_02086834(void *a, int b);
extern void func_0209f128(void *a, int b);
extern int data_021f3aa4;
extern int data_021dc7a8;
extern int func_02016104(void *p);
extern int func_0201c314(void *p, int x);
extern int func_020147fc(void *p, int a, int b, int c);
extern int func_02014868(void *ptr);
extern int func_0203e020(void *ptr);
extern void func_ov083_02278e98(void *ptr, int x);

int func_ov083_02278e08(int a, int *p);

int func_ov083_02278e64(char *self)
{

    func_02019d0c(self + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov083_02278e18(void *p)
{
    if (func_ov083_02278e08((int) p, (int *) ((char *) p + 0x654))) {
        return 1;
    }
    *(int *) ((char *) p + 0x654) = 0x258;
    {
        void *base = &data_021f3aa4;
        func_020861dc(base);
        func_02086834(base, 3);
        func_0209f128(&data_021dc7a8, 0xf);
    }
    return 1;
}

int func_ov083_02278e08(int a, int *p)
{
    if (*p != 0) {
        (*p)--;
    }
    return *p;
}

int func_ov083_02278dd0(void *self)
{
    int r1 = func_02016104((char *) self + 0x65c);
    int r2 = 0;
    if (r1 != 0) {
        r2 = func_0201c314(self, r1);
    }
    func_020147fc((char *) self + 0x618, 0, r2, 0);
    return 1;
}

int func_ov083_02278da4(struct ov083_02278da4_struct *p)
{
    if (func_02014868(&p->unk_618) == 0) {
        func_0203e020(p);
        func_ov083_02278e98(p, 2);
    }
    return 1;
}

int func_ov083_02278da0(void)
{
    return 1;
}
