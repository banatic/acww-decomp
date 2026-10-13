/* func_0204de34 @ 0x0204de34, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c80e0[5];
extern void func_0204de14(int element, int index);

void func_0204de34(void)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (data_021c80e0[i] != 0) {
            func_0204de14(data_021c80e0[i], i);
        }
    }
}
