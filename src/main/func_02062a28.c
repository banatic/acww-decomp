/* func_02062a28 @ 0x02062a28, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e6e4(int p0);
extern void *func_0206e7bc(void *a, unsigned int i);

extern unsigned char data_021cb5e0[];

void *func_02062a28(unsigned short *param)
{
    int flag = 0;
    unsigned short v = *param;
    int t;
    unsigned short w;
    int val;
    unsigned int u;
    void *p;
    void *ret;

    if ((unsigned int) v >= 0x1000 && (unsigned int) v <= 0x10ff) {
        flag = 1;
    }
    if (flag != 0) {
        if ((unsigned int) v >= 0x1000 && (unsigned int) v <= 0x10ff) {
            t = v - 0x1000;
        } else {
            t = -1;
        }
        t |= 3;
        if ((unsigned int) t < 0x100) {
            val = (unsigned short) (t + 0x1000);
        } else {
            val = 0x1000;
        }
        w = val;
        u = *(volatile unsigned short *) &w & 0xfff;
        if (u >= 0x56e) {
            u = 0x56d;
        }
        p = (void *) func_0206e6e4((int) (unsigned int) data_021cb5e0);
        ret = func_0206e7bc(p, u);
        if (ret != 0) {
            return ret;
        }
        return 0;
    } else {
        u = v & 0xfff;
        if (u >= 0x56e) {
            u = 0x56d;
        }
        p = (void *) func_0206e6e4((int) (unsigned int) data_021cb5e0);
        ret = func_0206e7bc(p, u);
        if (ret != 0) {
            return ret;
        }
        return 0;
    }
}
