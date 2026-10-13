/* func_020133b4 @ 0x020133b4, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02013420(void *a, int b, int c, void *d);
extern void MI_CpuCopy8(void *dst, const void *src, unsigned int n);

typedef struct {
    unsigned char lo : 4;
    unsigned char hi : 4;
} NibblePair;

void func_020133b4(void *obj, int p1, int p2, void *data)
{
    int count;
    unsigned char *p;
    NibblePair *np;

    count = func_02013420(obj, p1, p2, data);
    p = (unsigned char *) obj + 0x2c + 3 * count;
    while (count > 0) {
        MI_CpuCopy8(p - 3, p, 3);
        p -= 3;
        count--;
    }

    p1 &= 0xf;
    p2 &= 0xf;
    np = (NibblePair *) &p[2];
    np->hi = p1;
    np->lo = p2;
    p[0] = (unsigned char) ((int *) data)[0];
    p[1] = (unsigned char) ((int *) data)[1];
}
