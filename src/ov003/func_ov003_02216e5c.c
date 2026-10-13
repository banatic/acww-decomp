/* func_ov003_02216e5c @ 0x02216e5c, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200fa6c(void *dst, void *src);
extern void func_02010d88(void *dst, void *src, int a, int b);
extern void func_02089fc8(void *dst);

void func_ov003_02216e5c(void *src)
{
    char buf[16];
    func_0200fa6c(buf, src);
    func_02010d88(src, buf, 0xf33, 0x1000);
    func_02089fc8((char *) src + 0x1c4);
}
