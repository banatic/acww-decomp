/* func_ov104_0229caa0 @ 0x0229caa0, 0x64 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066650(void *);
extern int func_02065ec0(void *);
extern int func_ov104_0229dad8(void *);
extern void func_ov104_0229d938(void *, int, void *);

void func_ov104_0229caa0(char *p0, int p1)
{
    int i;
    int r;
    char *e;

    e = p0 + 0x2db4;
    for (i = 0; i < 10; i++) {
        if (p1 != 0 && (*(unsigned short *) (p0 + 0xb2) & (1 << i))) {
            func_02066650(e);
        } else {
            if (func_02065ec0(e) != 0) {
                r = func_ov104_0229dad8(p0);
                if (r != 0x21) {
                    func_ov104_0229d938(p0, r, e);
                }
            }
        }
        e += 0x100;
    }
}
