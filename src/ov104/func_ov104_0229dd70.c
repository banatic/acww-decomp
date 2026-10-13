/* func_ov104_0229dd70 @ 0x0229dd70, 0x28 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov104_0229dd00(void *);
extern int func_ov094_0229b19c(void *);

void func_ov104_0229dd70(void *self)
{
    if (func_ov094_0229b19c((char *) self + 0xd58)) {
        ((char *) self)[0xb4] = 0;
        func_ov104_0229dd00(self);
    }
}
