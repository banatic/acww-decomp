/* func_ov004_0220e3f0 @ 0x0220e3f0, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064328(void *, void *, int, int, int);
extern void *data_ov004_0224ffe4;
extern void *data_ov004_02256ea4;

void *func_ov004_0220e3f0(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_02064328(&data_ov004_02256ea4, &data_ov004_0224ffe4, (a1 >> 8), ((a1 & 0xff) >> 4), a1);
    return &data_ov004_02256ea4;
}
