/* func_02036960 @ 0x02036960, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02036f24(void *);
extern void func_020370b4(void *);
extern void func_020372b4(void *);

void func_02036960(void *arg0)
{
    void *r4;
    r4 = arg0;
    func_02036f24((char *) r4 + 0x24);
    func_020370b4((char *) r4 + 0x18);
    func_020372b4((char *) r4 + 4);
}
