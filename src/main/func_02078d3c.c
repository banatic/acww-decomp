/* func_02078d3c @ 0x02078d3c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0205c35c(void);
extern void func_02078cb0(void *ptr);
extern void func_020e9abc(void);
extern void *data_021c9ac4;
extern char data_021d12dc;

void func_02078d3c(void)
{
    func_0205c35c();
    func_02078cb0(&data_021d12dc);
    if (data_021c9ac4) {
        func_020e9abc();
    }
}
