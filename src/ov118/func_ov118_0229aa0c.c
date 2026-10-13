/* func_ov118_0229aa0c @ 0x0229aa0c, 0x8c bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov118_0229a460(void *p, int n);
extern int func_ov118_0229a9ac(void *p);
extern int func_ov118_0229a950(void *p);
extern void func_ov002_0220a0b4(void *p, int a, int b);
extern void func_ov118_0229ade0(void *p, int v, int n);
extern void func_ov002_0220a374(void *p, int n);
extern int func_ov118_0229a854(void *p);

int func_ov118_0229aa0c(void *arg0)
{
    if (func_ov118_0229a460(arg0, 8) == 0) {
        if (((unsigned char *) arg0)[0xac] == 16) {
            ((unsigned char *) arg0)[0xac] = 8;
        }
    }
    {
        int a = func_ov118_0229a9ac(arg0);
        int b = func_ov118_0229a950(arg0);
        func_ov002_0220a0b4((char *) arg0 + 0x6c0, a, b);
    }
    {
        unsigned char b = ((unsigned char *) arg0)[0xac];
        if (b >= 10 && b <= 15) {
            int v = *(unsigned short *) ((char *) arg0 + 0x98);
            v &= ~0xF;
            func_ov118_0229ade0(arg0, v, 0xF);
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
    return func_ov118_0229a854(arg0);
}
