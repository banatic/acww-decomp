/* func_ov004_02216694 @ 0x02216694, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0220d030(void *);
extern void func_ov004_02216110(void *);
extern void func_ov004_022163f8(void *);

int func_ov004_02216694(char *self)
{
    // DECLS
    // ENDDECLS
    func_ov004_02216110(self);
    func_ov004_022163f8(self);
    func_ov004_0220d030(self + 0x848);
    return 0x1;
}
