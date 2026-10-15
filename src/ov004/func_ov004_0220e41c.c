/* func_ov004_0220e41c @ 0x0220e41c, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064328(void *, void *, int, int, int);
extern void *data_ov004_0224fffc;
extern void *data_ov004_02256e7c;

void *func_ov004_0220e41c(char *self, int a1)
{
    // DECLS
    // ENDDECLS
    func_02064328(&data_ov004_02256e7c, &data_ov004_0224fffc, (a1 >> 8), ((a1 & 0xff) >> 4), a1);
    return &data_ov004_02256e7c;
}
