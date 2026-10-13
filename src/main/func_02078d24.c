/* func_02078d24 @ 0x02078d24, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02078c88(void *ptr);
extern void func_0205c340(void);

extern unsigned char data_021d12dc[];

void func_02078d24(void)
{
    void *ptr;
    ptr = (void *) data_021d12dc;
    func_02078c88(ptr);
    func_0205c340();
}
