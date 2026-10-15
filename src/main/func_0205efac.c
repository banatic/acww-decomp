/* func_0205efac @ 0x0205efac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205f00c(void *);
extern void func_020606c0(void *);

void *func_0205efac(void *self)
{
    func_0205f00c((char *) self + 8);
    func_020606c0((char *) self + 0x28);
    *((unsigned char *) self) = 9;
    *((unsigned int *) ((char *) self + 4)) = 0x1000;
    return self;
}
