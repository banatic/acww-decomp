/* func_0203d480 @ 0x0203d480, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203d32c(void *ptr);
extern void func_0203d320(void *ptr);
extern void func_0203d244(void *ptr);
extern char data_021c6998[];

void func_0203d480(int param)
{
    if (param == 1) {
        func_0203d32c(data_021c6998);
    } else {
        func_0203d320(data_021c6998);
    }
    func_0203d244(data_021c6998);
}
