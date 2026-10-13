/* func_02052a64 @ 0x02052a64, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int b0 : 4;
    unsigned int b4 : 4;
    unsigned int b8 : 4;
    unsigned int b12 : 1;
    unsigned int b13 : 1;
    unsigned int b14 : 1;
    unsigned int b15 : 16;
} BF;

extern void func_020523e4(int a0, int a1, int a2, int a3, int a4, int a5, int a6, unsigned short *a7, unsigned char a8);

void func_02052a64(int a0, BF *v)
{
    unsigned short t;
    int f13, f14;
    unsigned char f8, f12;
    unsigned short *p;
    unsigned char zero;

    t = v->b15;
    f13 = v->b13 != 0 ? 1 : 0;
    f14 = v->b14 != 0 ? 1 : 0;
    f8 = v->b8;
    p = &t;
    zero = 0;
    f12 = v->b12;
    func_020523e4(a0, v->b0, v->b4, f12, f13, f14, f8, p, zero);
}
