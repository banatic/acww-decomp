/* func_ov003_02234264 @ 0x02234264, 0x94 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov003_02235b54(void *a, int b, int c);
extern short func_ov003_0223418c(int a, int b);

void func_ov003_02234264(char *self)
{
    int r = func_ov003_02235b54(self, 0x50, 0xe38);
    if (r != 0) {
        int *d;
        int *s;
        if (*(unsigned char *) (self + 0x24a) != 0) {
            *(char *) (self + 0x251) = 0xf;
            *(int *) (self + 0x21c) |= 0xf00;
        } else {
            *(char *) (self + 0x251) = 0xd;
        }
        *(short *) (self + 0x240) = func_ov003_0223418c(*(short *) (self + 0x23a), r);
        *(int *) (self + 0x21c) += 1;
        *(short *) (self + 0x242) = 0;
        s = (int *) (self + 0x204);
        d = (int *) (self + 0x1d4);
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
    }
}
