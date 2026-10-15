/* func_ov102_0229d2a4 @ 0x0229d2a4, 0x7c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(void *p, void *q);
extern int func_ov102_0229d454(void *p, void *q);
extern int func_ov102_0229d400(void *p, void *q);
extern int func_ov102_0229d444(void *p, void *q);
extern void func_ov094_0229aa14(void *p, int r, int s, int t);
extern void func_ov094_0229a9b4(void *p, int r);

void func_ov102_0229d2a4(unsigned char *p1, void *p2, int p3, int p4)
{
    if (func_ov102_0229d464(p1, p2) || func_ov102_0229d454(p1, p2)) {
        int r = func_ov102_0229d400(p1, p2);
        func_ov094_0229aa14(p1 + 0xcc, r, p3, p4);
        func_ov094_0229a9b4(p1 + 0xcc, r);
    } else if (func_ov102_0229d444(p1, p2)) {
        unsigned char a = p1[0x25a3];
        int t = (a - 1) * 15;
        unsigned char b = p1[0x25a4];
        unsigned char *base = p1 + ((t + b) * 2);
        *(unsigned short *) (base + 0x24e8) = (unsigned short) p3;
    }
}
