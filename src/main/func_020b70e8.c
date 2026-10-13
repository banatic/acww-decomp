/* func_020b70e8 @ 0x020b70e8, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b7198(void);
extern void func_0204f8ec(int);
extern int data_020e54c0;
extern int data_020e54b8;

void func_020b70e8(void)
{
    func_020b7198();
    if (data_020e54c0 != -1) {
        func_0204f8ec(data_020e54c0);
        data_020e54c0 = -1;
    }
    if (data_020e54b8 != -1) {
        func_0204f8ec(data_020e54b8);
        data_020e54b8 = -1;
    }
}
