/* func_0209fdac @ 0x0209fdac, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02073100(void);
extern int __arm func_020eb2ec(void);
extern void func_02088250(void *ptr);
extern int data_021f3278;

int func_0209fdac(void)
{
    func_02073100();
    if (func_020eb2ec() != 0) {
        func_02088250(&data_021f3278);
        return 1;
    }
    return 0;
}
