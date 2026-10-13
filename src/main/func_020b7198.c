/* func_020b7198 @ 0x020b7198, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f8ec(int);
extern int data_020e54b4;
extern int data_020e54bc;

void func_020b7198(void)
{
    if (data_020e54b4 != -1) {
        func_0204f8ec(data_020e54b4);
        data_020e54b4 = -1;
    }
    if (data_020e54bc != -1) {
        func_0204f8ec(data_020e54bc);
        data_020e54bc = -1;
    }
}
