/* func_ov003_0221947c @ 0x0221947c, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_022195b0(void *a, unsigned short *b);
extern int func_ov003_022195c8(void *a, unsigned short b, int c, void *d);

void func_ov003_0221947c(void *r0, void *r1)
{
    unsigned short local;
    func_ov003_022195b0((char *) r0 + 0x8f0, &local);
    func_ov003_022195c8(r0, local, 5, r1);
}
