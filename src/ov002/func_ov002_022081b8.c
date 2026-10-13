/* func_ov002_022081b8 @ 0x022081b8, 0x22 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_020701e4(void *);
extern void func_020ee4d8(void *, int);

void func_ov002_022081b8(void *r0, int r1)
{
    void *r5 = r0;
    int r4 = r1;
    if (r4 == 2) {
        func_020701e4((char *) r5 + 0x64);
    }
    func_020ee4d8(r5, r4);
}
