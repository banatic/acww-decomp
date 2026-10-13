/* func_ov004_0223380c @ 0x0223380c, 0x30 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200451c(void *p);

void func_ov004_0223380c(void *self)
{
    int i;
    int z;
    char *p;

    p = (char *) self;
    i = 0;
    z = i;
    for (; i < 0xf; i++) {
        *(int *) (p + 4) = z;
        *(unsigned short *) (p + 8) = 0xfff1;
        *(unsigned short *) (p + 0xa) = 0xfff1;
        func_0200451c(p + 0x4c);
        p += 0x94;
    }
}
