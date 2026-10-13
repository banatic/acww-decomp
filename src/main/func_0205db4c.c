/* func_0205db4c @ 0x0205db4c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205db78(void *p);
extern void func_020e9b9c(void);

extern unsigned char data_021c9df4[];

void func_0205db4c(unsigned char *ptr, unsigned char value)
{
    func_0205db78((void *) data_021c9df4);
    func_020e9b9c();
    *ptr = value;
}
