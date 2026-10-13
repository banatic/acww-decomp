/* func_02084418 @ 0x02084418, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_020e54a8;
extern unsigned int data_021c80bc;
extern int func_0204f490(void *, int *, int *, int *, int *, unsigned short *, unsigned short *, int, int);
extern int func_0204f7ac(int *, int, int, int, int);

int func_02084418(void *unused, int *p1, short *p2)
{
    unsigned short h[2];
    int a, b, c, d;
    int r0;
    int ctx;

    r0 = (data_020e54a8 != 0) ? 0 : 1;

    if (r0 != 0) {
        ctx = data_021c80bc;
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        if (ctx != 0) {
            h[0] = 0x5014;
            h[1] = 0x501a;
            if (func_0204f490((void *) ctx, &a, &b, &c, &d, &h[0], &h[1], 1, 0) != 0) {
                func_0204f7ac(p1, a, b, c, d);
                p1[0] += 0x4000;
                p1[2] += 0x4000;
                p2[1] = (short) 0xffffc000;
                return 1;
            }
        }
    }
    return 0;
}
