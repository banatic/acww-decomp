/* map_menu_input_3: 3 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229aa0c @ 0x0229aa0c, 0x8c bytes, Thumb
 * func_ov118_0229a9ac @ 0x0229a9ac, 0x60 bytes, Thumb
 * func_ov118_0229a950 @ 0x0229a950, 0x5c bytes, Thumb
 */

extern int func_ov118_0229a460(void *p, int n);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov118_0229ade0(void *p, int v);
extern void func_ov002_0220a374(void *p, int n);
extern void func_ov118_0229a854(void *p);
extern int func_ov090_022990b8(int v);
extern int func_ov002_0220a4f8(void *p);
extern int func_ov002_0220a4d4(const unsigned char *p);

int func_ov118_0229a9ac(char *p);
int func_ov118_0229a950(const unsigned char *p);

void func_ov118_0229aa0c(void *arg0)
{
    if (func_ov118_0229a460(arg0, 8) == 0) {
        if (((unsigned char *) arg0)[0xac] == 16) {
            ((unsigned char *) arg0)[0xac] = 8;
        }
    }
    {
        int a = func_ov118_0229a9ac((char *) arg0);
        int b = func_ov118_0229a950((const unsigned char *) arg0);
        func_ov002_0220a0b4((char *) arg0 + 0x6c0, a, b);
    }
    {
        unsigned char b = ((unsigned char *) arg0)[0xac];
        if (b >= 10 && b <= 15) {
            int v = *(unsigned short *) ((char *) arg0 + 0x98);
            v &= ~0xF;
            func_ov118_0229ade0(arg0, v);
        }
    }
    {
        unsigned char b2 = ((unsigned char *) arg0)[0xac];
        if (b2 <= 7) {
            func_ov002_0220a374((char *) arg0 + 0x6c0, 13);
        } else {
            func_ov002_0220a374((char *) arg0 + 0x6c0, 1);
        }
    }
    func_ov118_0229a854(arg0);
}

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

int func_ov118_0229a950(const unsigned char *p)
{
    unsigned char v;

    if (func_ov118_0229a460((void *) p, 0x800) != 0) {
        return p[0xaf];
    }

    v = p[0xac];

    if (v >= 10 && v <= 15) {
        return (v - 10) * 16 + 0x58;
    }

    if (v >= 8 && v <= 9) {
        return 0x40;
    }

    if (v <= 7) {
        return 8;
    }

    if (v == 16) {
        return func_ov002_0220a4d4(p + 0x678);
    }

    return 0x60;
}
