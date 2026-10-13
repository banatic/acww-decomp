/* func_ov003_022127a0 @ 0x022127a0, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02212824(void *, int *);
extern void func_ov003_02212818(void *, int *);
extern void func_020109fc(void *, int, int, int);

void func_ov003_022127a0(void *self, void *data)
{
    unsigned char *p = (unsigned char *) data + 0xc;
    int b1 = p[1];
    unsigned char *d = (unsigned char *) self + 0x7d4;
    int b0 = p[0];
    int loc[2], loc2[2];

    loc[0] = b0;
    loc[1] = b1;
    func_ov003_02212824(d, loc);
    if (*(int *) ((char *) self + 0x80c) == -1) {
        d[2] = 0;
    } else {
        d[2] = 1;
    }
    loc2[0] = b0;
    loc2[1] = b1;
    func_ov003_02212818((char *) self + 0x8f0, loc2);
    if (*(int *) ((char *) self + 0x704) == 0x4a) {
        func_020109fc(self, 0x4a, 3, 0);
    }
}
