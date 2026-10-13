/* func_020f0df0 @ 0x020f0df0, 0x44 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_0213e858;
extern void func_020eedb8(void *a, int b, void *c);
extern void func_0210b634(void *a, unsigned short b, void *c);

void func_020f0df0(char *a, void *b, void *c)
{
    func_020eedb8(b, 0, a + 0x38);
    func_0210b634(a + 0x38, data_0213e858, c);
}
