/* func_020b88d8 @ 0x020b88d8, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d227c[];
extern void func_020b9068(void *, unsigned char);

void func_020b88d8(void *self)
{
    func_020b9068((char *) self + 8, data_020d227c[*(unsigned int *) ((char *) self + 0xfc)]);
}
