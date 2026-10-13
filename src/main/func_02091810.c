/* func_02091810 @ 0x02091810, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020913c8(void *dst, const void *src, unsigned int size);

extern unsigned char data_021d52d8[];

void func_02091810(void *src)
{
    func_020913c8((void *) data_021d52d8, src, 4);
}
