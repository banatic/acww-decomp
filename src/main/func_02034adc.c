/* func_02034adc @ 0x02034adc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034c64(void *dst, void *src);
extern void *func_02034b04(void *dst, void *src, void *a, void *b);

void func_02034adc(void *a, void *b, void *c, void *d)
{
    void *sp;
    func_02034c64(&sp, a);
    func_02034b04(&sp, b, c, d);
}
