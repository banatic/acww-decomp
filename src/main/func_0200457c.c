/* func_0200457c @ 0x0200457c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f0f34(void *param1, void *param2);

extern unsigned char data_021fd1bc[];

void func_0200457c(void *param1)
{
    void *addr = (void *) data_021fd1bc;
    func_020f0f34(addr, param1);
}
