/* villager_talk_picks_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020267d0 @ 0x020267d0, 0x34 bytes, Thumb
 * func_0202678c @ 0x0202678c, 0x44 bytes, Thumb
 * func_02026748 @ 0x02026748, 0x44 bytes, Thumb
 * func_02026714 @ 0x02026714, 0x34 bytes, Thumb
 */

extern int func_0202d190(void *a, int b, int c, unsigned char d);

void func_020267d0(unsigned short *a, unsigned char *b)
{
    *a = 0xFFF1;
    if (func_0202d190(a, 0, 1, b[4]) == 0) {
        func_0202d190(a, 2, 4, b[4]);
    }
}

void func_0202678c(unsigned short *out, void *src)
{
    int zero = 0;
    *out = 0xfff1;
    if (func_0202d190((void *) out, 1, 2, *(unsigned char *) ((char *) src + 4)) != 0) {
        return;
    }
    if (func_0202d190((void *) out, zero, zero, *(unsigned char *) ((char *) src + 4)) != 0) {
        return;
    }
    func_0202d190((void *) out, 3, 4, *(unsigned char *) ((char *) src + 4));
}

void func_02026748(unsigned short *s, unsigned char *t)
{
    int r;

    *s = 0xfff1;
    r = func_0202d190((void *) s, 2, 3, t[4]);
    if (r != 0) {
        return;
    }
    r = func_0202d190((void *) s, 0, 1, t[4]);
    if (r != 0) {
        return;
    }
    r = 4;
    func_0202d190((void *) s, r, r, t[4]);
}

void func_02026714(unsigned short *out, unsigned char *in)
{
    *out = 0xfff1;
    if (func_0202d190(out, 3, 4, in[4]) == 0) {
        func_0202d190(out, 0, 2, in[4]);
    }
}
