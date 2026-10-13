/* func_0203f5a4 @ 0x0203f5a4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021eed68;
extern int func_0207813c(void *p);
extern void func_02078130(void *p, unsigned short v);
extern void func_02077ed4(void *p);

int func_0203f5a4(void *self)
{
    char *base = &data_021eed68;
    unsigned short v = *(unsigned short *) ((char *) self + 0xC0);
    if (v != func_0207813c(base)) {
        func_02078130(base, v);
        func_02077ed4(self);
        return 1;
    } else {
        return 0;
    }
}
