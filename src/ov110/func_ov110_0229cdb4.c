/* func_ov110_0229cdb4 @ 0x0229cdb4, 0x2c bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02209f3c(void *);
extern int func_ov002_02209f14(void *);

void func_ov110_0229cdb4(void *p)
{
    char *base = (char *) p;
    *(int *) (base + 0xa8) = func_ov002_02209f3c(base + 0x22e0) - 2;
    *(int *) (base + 0xac) = func_ov002_02209f14((int *) base + 0x8b8) - 4;
}
