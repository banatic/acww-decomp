/* func_ov003_022169a4 @ 0x022169a4, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02216a70(void *base, unsigned char *a, unsigned char *b, unsigned char *c, unsigned char *d,
                                unsigned char *e);
extern int func_ov003_02216ab8(void *obj, unsigned char a, int b, void *c, int d, int e);

void func_ov003_022169a4(void *obj, int param)
{
    unsigned char buf[5];
    unsigned int vals[2];

    func_ov003_02216a70((char *) obj + 0x8f0, buf, buf + 1, buf + 2, buf + 3, buf + 4);

    *((unsigned char *) ((char *) obj + 0x16c)) = buf[2];

    if (buf[1] == 0) {
        vals[0] = buf[3];
        vals[1] = buf[4];
        func_ov003_02216ab8(obj, buf[0], 0, vals, 6, param);
    }
}
