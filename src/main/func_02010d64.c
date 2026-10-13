/* func_02010d64 @ 0x02010d64, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010e48(char *a, char *b);
extern void func_02089fc8(char *a);

void func_02010d64(char *p)
{
    func_02010e48(p, p + 0x7f0);
    func_02089fc8(p + 0x174);
}
