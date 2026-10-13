/* func_02036980 @ 0x02036980, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020372bc(void *);
extern void func_020370bc(void *);
extern void func_02036f2c(void *);

void func_02036980(void *arg0)
{
    void *r4 = arg0;
    func_020372bc((char *) r4 + 4);
    func_020370bc((char *) r4 + 0x18);
    func_02036f2c((char *) r4 + 0x24);
}
