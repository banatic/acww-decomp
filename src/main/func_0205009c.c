/* func_0205009c @ 0x0205009c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020dcd78;
extern int data_021c8184;
extern void func_020505f4(unsigned int, int);
extern void func_0209d138(unsigned int);

int func_0205009c(unsigned int param)
{
    int i;
    for (i = 0; i < data_020dcd78; i++) {
        func_020505f4(param, i);
    }
    func_0209d138(param + 0x600);
    data_021c8184 = 0;
    return 1;
}
