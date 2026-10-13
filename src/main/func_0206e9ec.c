/* func_0206e9ec @ 0x0206e9ec, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02004158(void *dst, const void *src, unsigned int size);

extern unsigned char data_021cfbcc[];

void func_0206e9ec(void *dst, const void *src)
{
    func_02004158((void *) data_021cfbcc, dst, (unsigned int) src);
}
