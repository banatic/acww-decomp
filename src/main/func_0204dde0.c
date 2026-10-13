/* func_0204dde0 @ 0x0204dde0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e9b9c(int *ptr);
extern void func_0204dd84(int *ptr);
extern int *data_021c9b34;
extern int *data_021c80e0[5];

void func_0204dde0(void)
{
    int i;
    func_020e9b9c(data_021c9b34);
    for (i = 0; i < 5; i++) {
        if (data_021c80e0[i] != 0) {
            func_0204dd84(data_021c80e0[i]);
        }
    }
}
