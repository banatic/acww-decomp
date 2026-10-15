/* func_ov077_02278d7c @ 0x02278d7c, 0x58 bytes, Thumb, module ov077
 * mwccarm 1.2/base -O1,s
 */

extern int func_0206fbc0(void);
extern int func_0206fc6c(void);
extern int func_020644cc(int);
extern void func_0206844c(void *, void *, void *);
extern void func_ov077_02278e10(void *, int);
extern void *data_ov077_02279700;

void func_ov077_02278d7c(void *p0)
{
    unsigned char buf[4];
    void *p = *(void **) ((char *) p0 + 0x40);

    if (func_0206fbc0() != 0) {
        register unsigned char v = 0x18;
        register unsigned char *q = buf;
        q[0] = v;
        if (func_0206fc6c() != 0) {
            if (func_020644cc(2) == 0) {
                buf[0] = 0x1a;
            } else {
                buf[0] = 0x19;
            }
        }
        func_0206844c(p, buf, data_ov077_02279700);
        func_ov077_02278e10(p0, 0);
    }
}
