/* func_02078a5c @ 0x02078a5c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078c2c(void *param1, void *param2);

extern unsigned char data_021d1310[];

void func_02078a5c(void *param)
{
    void *addr = (void *) data_021d1310;
    func_02078c2c(addr, *(void **) param);
}
