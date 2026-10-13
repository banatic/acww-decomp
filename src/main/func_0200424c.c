/* func_0200424c @ 0x0200424c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f1ba4(void *dst, const void *src, unsigned int size);

extern unsigned char data_021fd1bc[];

void func_0200424c(void *dst, const void *src)
{
    func_020f1ba4((void *) data_021fd1bc, dst, (unsigned int) src);
}
