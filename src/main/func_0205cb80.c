/* func_0205cb80 @ 0x0205cb80, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c9b58[];
extern void func_0205cd4c(void *ptr, unsigned char cmd);

void func_0205cb80(unsigned char *p)
{
    func_0205cd4c(data_021c9b58, *p);
}
