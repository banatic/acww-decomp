/* scene_kinds: 10 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b6840 @ 0x020b6840, 0x6c bytes, Thumb
 * func_020b682c @ 0x020b682c, 0x14 bytes, Thumb
 * func_020b6818 @ 0x020b6818, 0x12 bytes, Thumb
 * func_020b6804 @ 0x020b6804, 0x12 bytes, Thumb
 * func_020b67e8 @ 0x020b67e8, 0x1a bytes, Thumb
 * func_020b67d4 @ 0x020b67d4, 0x12 bytes, Thumb
 * func_020b67c0 @ 0x020b67c0, 0x12 bytes, Thumb
 * func_020b67ac @ 0x020b67ac, 0x12 bytes, Thumb
 * func_020b679c @ 0x020b679c, 0x10 bytes, Thumb
 * func_020b6788 @ 0x020b6788, 0x12 bytes, Thumb
 */

extern int func_020b64c0(int k);
extern void *data_021f42f4;
extern unsigned char data_020e54a8;
extern unsigned char data_020d2150[];
extern unsigned int *data_021f6948;
extern unsigned char func_020b65c4(void);

int func_020b6840(int arg)
{
    void *o;
    int res;
    unsigned short v;
    int fa;
    int fb;
    unsigned int t;

    res = 0;
    o = data_021f42f4;
    if (o != 0) {
        v = *(unsigned short *) ((char *) o + 0xc);
        fa = 1;
        fb = 1;
        t = (data_020e54a8 == 0) ? 1 : 0;
        if (t == 0) {
            t = (data_020e54a8 == 1) ? 1 : 0;
            if (t == 0) {
                fb = 0;
            }
        }
        if (fb == 0) {
            if (arg == 0 || v != 5) {
                fa = 0;
            }
        }
        if (fa != 0) {
            int k = (int) func_020b65c4();
            if (func_020b64c0(k) != 0) {
                res = data_020d2150[k];
            }
        }
    }
    return res;
}

int func_020b682c(void)
{
    unsigned int *ptr;
    int result;

    result = 0;
    ptr = data_021f6948;
    if (ptr != 0) {
        result = *(int *) ((char *) ptr + 8);
    }
    return result;
}

int func_020b6818(unsigned int x)
{
    if (x >= 1 && x <= 5) {
        return x - 1;
    }
    return -1;
}

int func_020b6804(void)
{
    return func_020b6818((unsigned int) func_020b65c4());
}

int func_020b67e8(unsigned int x)
{
    int result;
    int r0;
    int r2;

    r0 = func_020b6818(x);
    r2 = 0;
    if (r0 != ~r2) {
        r2 = 1;
    }
    result = r2;
    return result;
}

int func_020b67d4(void)
{
    return func_020b67e8(func_020b65c4());
}

int func_020b67c0(int param)
{
    if ((unsigned char) (param + 0xfa) > 2) {
        return 0;
    } else {
        return 1;
    }
}

int func_020b67ac(void)
{
    return func_020b67c0((int) func_020b65c4());
}

int func_020b679c(int x)
{
    switch (x) {
        case 6:
        case 7:
            return 1;
    }
    return 0;
}

int func_020b6788(void)
{
    return func_020b679c((int) func_020b65c4());
}
