/* field_actor_motion: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0201005c @ 0x0201005c, 0x5c bytes, Thumb
 * func_02010030 @ 0x02010030, 0x2c bytes, Thumb
 * func_02010004 @ 0x02010004, 0x2c bytes, Thumb
 */

extern int func_020ea990(void *p, void *);
extern int func_020e8ed8(int a, int b);
extern int func_020e8b4c(int a, short b);
extern int data_020c766c[];
extern unsigned char data_020e54a8;
extern int func_ov004_02225ef8(int a);
extern int func_ov003_0220c57c(int a);
extern int func_ov004_02225fb8(void *self, int action, int mode);
extern int func_ov003_0220c328(void *self, void *arg1, ...);

int func_0201005c(unsigned char *self, unsigned char *other, int index)
{
    if (func_020ea990(self + 0x6f4, other) >= ((data_020c766c[index] << 13) >> 12)) {
        goto ret0;
    }

    {
        int d0 = *(int *) (other + 0) - *(int *) (self + 0x6f4);
        int d1 = *(int *) (other + 8) - *(int *) (self + 0x6fc);
        int v = func_020e8ed8(d0, d1);
        if (func_020e8b4c(v, *(short *) (self + 0x8e)) >= 0x2aaa) {
            goto ret0;
        }
    }
    return 1;
ret0:
    return 0;
}

int func_02010030(int a)
{
    unsigned int ok;
    if (data_020e54a8 == 1) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok > 0) {
        return func_ov004_02225ef8(a);
    } else {
        return func_ov003_0220c57c(a);
    }
}

int func_02010004(int a, int b)
{
    unsigned int flag;
    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag != 0) {
        return func_ov004_02225fb8((void *) a, b, 0);
    } else {
        return func_ov003_0220c328((void *) a, (void *) b);
    }
}
