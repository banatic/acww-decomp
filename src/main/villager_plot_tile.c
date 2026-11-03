/* villager_plot_tile: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02081fa0 @ 0x02081fa0, 0x10 bytes, Thumb
 * func_02081f9c @ 0x02081f9c, 0x2 bytes, Thumb
 * func_02081f94 @ 0x02081f94, 0x8 bytes, Thumb
 * func_02081f80 @ 0x02081f80, 0x14 bytes, Thumb
 * func_02081f78 @ 0x02081f78, 0x6 bytes, Thumb
 * func_02081f60 @ 0x02081f60, 0x18 bytes, Thumb
 */

struct Pair {
    unsigned int a;
    unsigned int b;
};

void func_02081f94(unsigned char *p0);

int func_02081fa0(int a)
{
    func_02081f94((unsigned char *) a);
    return a;
}

void func_02081f9c(void *object) {}

void func_02081f94(unsigned char *p0)
{
    p0[0] = 255;
    p0[1] = 255;
}

int func_02081f80(const unsigned char *p)
{
    if (p[0] != 0xff && p[1] != 0xff) {
        return 1;
    } else {
        return 0;
    }
}

void func_02081f78(unsigned char *p, int a, int b)
{
    p[0] = (unsigned char) a;
    p[1] = (unsigned char) b;
}

void func_02081f60(int a, struct Pair *p)
{
    func_02081f78((unsigned char *) a, (unsigned char) ((unsigned char) p->a), (unsigned char) ((unsigned char) p->b));
}
