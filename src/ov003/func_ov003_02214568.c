/* func_ov003_02214568 @ 0x02214568, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200fa6c(void *dst, void *src);
extern void func_02010d88(void *dst, void *src, int a, int b);
extern void func_02089fc8(void *dst);

void func_ov003_02214568(void *arg0)
{
    char local[16];
    func_0200fa6c(local, arg0);
    func_02010d88(arg0, local, 0x99a, 0x1000);
    func_02089fc8((char *) arg0 + 0x1c4);
}
