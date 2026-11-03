/* xct_exchange_3: 6 functions, module ov055
 * mwccarm 1.2/base -O4,s
 * func_ov055_02260af0 @ 0x02260af0, 0x34 bytes, Thumb
 * func_ov055_02260ac8 @ 0x02260ac8, 0x28 bytes, Thumb
 * func_ov055_02260aac @ 0x02260aac, 0x1c bytes, Thumb
 * func_ov055_02260a78 @ 0x02260a78, 0x34 bytes, Thumb
 * func_ov055_02260a74 @ 0x02260a74, 0x4 bytes, Thumb
 * func_ov055_02260a70 @ 0x02260a70, 0x4 bytes, Thumb
 */

typedef struct {
    char pad_00[0x618];
    int unk_618;
} UnkStruct_02260a78;

extern int func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
extern unsigned short data_020c80f8;
extern unsigned char data_021c75b8;
extern void func_ov055_02260b24(int a, int b);
extern int func_020147e0(int a, int b, int c);
extern int func_02014868(const void *);
extern int func_020b5e10(void);
extern int func_020b6434(int, int, int, int);

int func_ov055_02260af0(void *arg)
{
    func_02019d0c((char *) arg + 0x564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    return 1;
}

int func_ov055_02260ac8(int param)
{
    unsigned int flag = (data_021c75b8 == 2) ? 1 : 0;
    if (flag != 0) {
        func_ov055_02260b24(param, 1);
    }
    return 1;
}

int func_ov055_02260aac(int a)
{
    func_020147e0(a + 0x618, 0, 1);
    return 1;
}

int func_ov055_02260a78(UnkStruct_02260a78 *self)
{
    if (func_02014868(&self->unk_618) == 0) {
        int two = 2;
        func_020b6434(func_020b5e10(), 0x2C, two, two);
        func_ov055_02260b24((int) self, 2);
    }
    return 1;
}

int func_ov055_02260a74(void)
{
    return 1;
}

int func_ov055_02260a70(void)
{
    return 1;
}
