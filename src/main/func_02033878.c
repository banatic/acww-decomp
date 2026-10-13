/* func_02033878 @ 0x02033878, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *p, int a, int b, const void *c);

extern void func_020339b8(void);

void *func_02033878(void *p)
{
    func_02138c48(p, 0x18, 0x30, (const void *) func_020339b8);
    return p;
}
