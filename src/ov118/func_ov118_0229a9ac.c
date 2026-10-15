/* func_ov118_0229a9ac @ 0x0229a9ac, 0x60 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229a460(void *p, int v);
extern int func_ov090_022990b8(int v);
extern int func_ov002_0220a4f8(void *p);

int func_ov118_0229a9ac(char *p)
{
    unsigned int v;
    if (func_ov118_0229a460(p, 0x800)) {
        return *(unsigned char *) (p + 0xae);
    }
    v = *(unsigned char *) (p + 0xac);
    if (v >= 10 && v <= 15) {
        return 0xa0;
    }
    if (v <= 7) {
        return func_ov090_022990b8(v);
    }
    if (v == 8) {
        return 0xd8;
    }
    if (v == 9) {
        return 0xb4;
    }
    if (v == 0x10) {
        return func_ov002_0220a4f8(p + 0x678);
    }
    return 0x80;
}
