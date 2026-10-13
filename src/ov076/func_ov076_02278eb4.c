/* func_ov076_02278eb4 @ 0x02278eb4, 0x58 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O1,s
 */

extern int func_0206fc6c(void *);
extern int func_0206fc8c(void);
extern void func_0209a050(void);
extern void func_02015330(void *, unsigned short *, int, int, int);
extern void func_0206844c(void *, void *, void *);
extern char data_ov076_022796e0;

void func_ov076_02278eb4(void *p0)
{
    unsigned char buf[4];
    void *p = *(void **) ((char *) p0 + 0x40);

    {
        register unsigned char v = 5;
        register unsigned char *q = buf;
        q[0] = v;
        if (func_0206fc6c(q) != 0) {
            if (func_0206fc8c() >= 0) {
                func_0209a050();
            }
            *(unsigned short *) &buf[2] = 0x1559;
            func_02015330(p0, (unsigned short *) &buf[2], 0, 5, 0);
            buf[0] = 6;
        }
    }
    func_0206844c(p, buf, &data_ov076_022796e0);
}
