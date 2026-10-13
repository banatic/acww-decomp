/* func_020ae03c @ 0x020ae03c, 0x154 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ae3c4(void *p);
extern unsigned int func_0205be44(void);
extern unsigned int func_020644cc(unsigned int max);
extern void func_02063ccc(void *p, int c, unsigned int n);
extern void func_020638d4(void *dest, void *src, int a, int b, int c, unsigned int d, int e);
extern void func_02063cc8(void *p);
extern unsigned int func_0205be20(void);
extern unsigned int func_0205be2c(void);
extern const unsigned char data_020d1e48[];

void func_020ae03c(unsigned short *out)
{
    unsigned int one = 1;
    unsigned char buf[0x34];
    unsigned int i, r;
    unsigned int t1, t2;
    const unsigned char *p;

    func_020ae3c4(out);

    t1 = func_0205be44() / 10 + 0x32;

    if (func_020644cc(100) < t1) {
        func_02063ccc(buf + 0x10, 0, 0x26);
        func_020638d4(buf, buf + 0x10, 0, 0, 0, one, 0);
        *out = *(unsigned short *) buf;
        func_02063cc8(buf + 0x10);
    } else {
        func_02063ccc(buf + 0x18, 0, 0x27);
        func_020638d4(buf + 2, buf + 0x18, 0, 0, 0, one, 0);
        *out = *(unsigned short *) (buf + 2);
        func_02063cc8(buf + 0x18);
    }

    t2 = (int) (func_0205be20() + func_0205be2c()) / 10 + 0x32;

    for (i = 1; i < 3; i++) {
        if (func_020644cc(100) < t2) {
            func_02063ccc(buf + 0x20, 0, 5);
            func_020638d4(buf + 4, buf + 0x20, 0, 0, 0, one, 0);
            out[i] = *(unsigned short *) (buf + 4);
            func_02063cc8(buf + 0x20);
        } else {
            func_02063ccc(buf + 0x28, 0, 0);
            func_020638d4(buf + 6, buf + 0x28, 0, 0, 0, one, 0);
            out[i] = *(unsigned short *) (buf + 6);
            func_02063cc8(buf + 0x28);
        }
    }

    *(unsigned short *) (buf + 8) = 0xfff1;
    *(unsigned short *) (buf + 10) = 0xfff1;
    *(unsigned short *) (buf + 12) = 0xfff1;

    for (i = 0; i < 3; i++) {
        ((unsigned short *) (buf + 8))[i] = out[i];
    }

    r = func_020644cc(6);
    for (i = 0, p = &data_020d1e48[3 * r]; i < 3; i++) {
        out[i] = ((unsigned short *) (buf + 8))[p[i]];
    }
}