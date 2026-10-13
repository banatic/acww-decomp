/* func_ov125_0229fefc @ 0x0229fefc, 0x64 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e4bc(void *);
extern int func_ov125_0229fe58(void *);
extern int func_ov002_0220a700(void *);
extern int func_ov002_0220a6e0(void *);
extern int func_ov002_0220a768(void *, int);
extern int func_ov002_0220a72c(void *, int);
extern void func_ov002_0220a0b4(void *, int, int);

void func_ov125_0229fefc(void *arg0)
{
    if (func_ov002_0220a700((char *) arg0 + 0x6a8)) {
        if (func_0208e4bc((char *) arg0 + 0x644)) {
            int r4 = func_ov002_0220a6e0((char *) arg0 + 0x6a8);
            int r6 = func_ov002_0220a768((char *) arg0 + 0x6a8, -1);
            int r2 = func_ov002_0220a72c((char *) arg0 + 0x6a8, -1);
            func_ov002_0220a0b4((char *) arg0 + 0x644, r4 + r6, r4 + r2);
        }
    } else {
        func_ov125_0229fe58(arg0);
    }
}
