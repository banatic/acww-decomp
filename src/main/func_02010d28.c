/* func_02010d28 @ 0x02010d28, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010e10(void *p1, void *p2);
extern void func_02089fc8(void *p);
extern void func_02010dc8(void *p, void *q);

void func_02010d28(void *param1, void *param2)
{
    func_02010e10(param1, (char *) param1 + 0x7f0);
    func_02089fc8((char *) param1 + 0x174);
    func_02010dc8(param1, param2);
    func_02089fc8((char *) param1 + 0x1c4);
}
