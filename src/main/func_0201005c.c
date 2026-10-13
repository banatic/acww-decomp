/* func_0201005c @ 0x0201005c, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ea990(void *p);
extern int func_020e8ed8(int a, int b);
extern int func_020e8b4c(int a, short b);
extern int data_020c766c[];

int func_0201005c(unsigned char *self, unsigned char *other, int index)
{
    if (func_020ea990(self + 0x6f4) >= ((data_020c766c[index] << 13) >> 12)) {
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
