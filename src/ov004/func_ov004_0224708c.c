/* func_ov004_0224708c @ 0x0224708c, 0x40 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ad58(int);
extern int func_0203c99c(void *, int);
extern void func_0203caa4(void *, int, int, void *);
extern void *data_020ca158;

int func_ov004_0224708c(char *self)
{
    // DECLS
    // ENDDECLS
    func_0203caa4(self, *(int *) ((char *) &data_020ca158 + (0xc * *(int *) (self + 0x1f0)) + (*(int *) (self + 0x1ec) << 2)),
                  0x0, &data_020ca158);
    func_0203ad58(func_0203c99c(self, 0x0));
    return 0x1;
}
