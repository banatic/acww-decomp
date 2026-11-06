/* scene_heaps: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0205c340 @ 0x0205c340, 0x1c bytes, Thumb
 * func_0205c300 @ 0x0205c300, 0x40 bytes, Thumb
 * func_0205c2e4 @ 0x0205c2e4, 0x1c bytes, Thumb
 * func_0205c2a0 @ 0x0205c2a0, 0x44 bytes, Thumb
 * func_0205c284 @ 0x0205c284, 0x1c bytes, Thumb
 * func_0205c200 @ 0x0205c200, 0x84 bytes, Thumb
 * func_0205c1e0 @ 0x0205c1e0, 0x20 bytes, Thumb
 * func_0205c1a4 @ 0x0205c1a4, 0x3c bytes, Thumb
 * func_0205c188 @ 0x0205c188, 0x1c bytes, Thumb
 * func_0205c158 @ 0x0205c158, 0x30 bytes, Thumb
 * func_0205c13c @ 0x0205c13c, 0x1c bytes, Thumb
 * func_0205c10c @ 0x0205c10c, 0x30 bytes, Thumb
 * func_0205c0f0 @ 0x0205c0f0, 0x1c bytes, Thumb
 */

extern int data_021c9ac4;
extern int data_020cd41c;
extern int data_020cd420;
extern unsigned int data_021c9ac0;
extern __arm unsigned int func_020ea0e0(unsigned int, int);
extern void func_020e9fc8(void *arg);
extern int func_02085f08(void);
extern int data_020cd410;
extern int data_020cd414;
extern unsigned int data_021c9abc;
extern unsigned char data_020e54a8;
extern unsigned int data_021c9ab8;
extern unsigned int func_02082240(void);
extern unsigned char func_020b65c4(void);
extern unsigned int func_020b5df8(unsigned int);
extern unsigned int func_020b5e04(unsigned int);
extern unsigned int func_02078d80(void);
extern unsigned int func_02078d78(void);
extern unsigned int func_020952e4(void);
extern unsigned int func_020952e0(void);
extern unsigned int func_020ea1bc(unsigned int, unsigned int);
extern unsigned int data_021c9ab4;
extern unsigned int data_020c9fd0;
extern unsigned int data_021c9ab0;
extern unsigned int data_020c9fcc;
extern unsigned int data_021c9b34;

void func_0205c340(void)
{
    func_020e9fc8((void *) data_021c9ac4);
    data_021c9ac4 = 0;
}

unsigned int func_0205c300(int param)
{
    unsigned int size = 0;
    unsigned int mask = ~(data_020cd41c - 1);
    unsigned int term;

    term = ((data_020cd420 + (data_020cd41c - 1)) & mask) + 0x48;
    term = (term + (data_020cd41c - 1)) & mask;
    size = size + (term << 3);
    return data_021c9ac0 = func_020ea0e0(size, param);
}

void func_0205c2e4(void)
{
    func_020e9fc8((*(void **) &data_021c9ac0));
    (*(void **) &data_021c9ac0) = 0;
}

unsigned int func_0205c2a0(int param)
{
    int count = func_02085f08();
    unsigned int size = 0;
    unsigned int mask = ~(data_020cd410 - 1);
    unsigned int term;

    term = ((data_020cd414 + (data_020cd410 - 1)) & mask) + 0x48;
    term = (term + (data_020cd410 - 1)) & mask;
    size = size + term * count;
    return data_021c9abc = func_020ea0e0(size, param);
}

void func_0205c284(void)
{
    func_020e9fc8((*(void **) &data_021c9abc));
    (*(void **) &data_021c9abc) = 0;
}

unsigned int func_0205c200(int param)
{
    unsigned int count1;
    unsigned int count2;
    unsigned int size;

    size = 0;

    {
        unsigned int cond = data_020e54a8 ? 0 : 1;

        if (cond > 0) {
            count1 = func_02082240();
        } else {
            count1 = func_020b5df8((unsigned int) func_020b65c4());
            count1 -= func_020b5e04((unsigned int) func_020b65c4());
        }
    }

    count2 = (unsigned int) func_02085f08();

    {
        unsigned int term1 = ((((func_02078d80() + 3) & ~3u) + 0x4b) & ~3u);
        size = size + term1 * count1;
    }
    {
        unsigned int term2 = ((((func_02078d78() + 3) & ~3u) + 0x4b) & ~3u);
        size = size + term2 * count2;
    }

    if (size != 0) {
        data_021c9ab8 = func_020ea0e0(size, param);
    }

    return data_021c9ab8;
}

void func_0205c1e0(void)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (data_021c9ab8)) != 0) {
        func_020e9fc8(condition_value0);
    }
    data_021c9ab8 = 0;
}

void func_0205c1a4(unsigned int arg)
{
    unsigned int len = 0;
    unsigned int total = len;
    unsigned int extra;

    len += (func_020952e4() + 3) & ~3;
    extra = func_020952e0();
    extra = ~(extra - 1) & (extra + 15);
    total += (len + extra) << 2;
    data_021c9ab4 = func_020ea1bc(total, arg);
}

void func_0205c188(void)
{
    func_020e9fc8((*(void **) &data_021c9ab4));
    (*(void **) &data_021c9ab4) = 0;
}

void func_0205c158(int param)
{
    unsigned int size = 0;
    size = size + ((((data_020c9fd0 + 3) & ~3u) + 0x4b) & ~3u);
    data_021c9ab0 = func_020ea0e0(size, param);
}

void func_0205c13c(void)
{
    func_020e9fc8((void *) data_021c9ab0);
    data_021c9ab0 = 0;
}

void func_0205c10c(int param)
{
    unsigned int size = 0;
    size = size + ((((data_020c9fcc + 3) & ~3u) + 0x4b) & ~3u);
    data_021c9b34 = func_020ea0e0(size, param);
}

void func_0205c0f0(void)
{
    func_020e9fc8((*(void **) &data_021c9b34));
    (*(void **) &data_021c9b34) = 0;
}
