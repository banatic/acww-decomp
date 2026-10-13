/* func_ov120_0229b740 @ 0x0229b740, 0x44 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov120_0229a6d0(void *);
extern int func_ov120_0229a448(void *, int);
extern void func_ov002_02208098(void *, int);

void func_ov120_0229b740(void *p)
{
    if (func_0208e484((char *) p + 0x6bc)) {
        func_ov120_0229a6d0(p);
        if (func_ov120_0229a448(p, 0x800)) {
            func_ov002_02208098(p, 9);
        } else {
            func_ov002_02208098(p, 2);
        }
    }
}
