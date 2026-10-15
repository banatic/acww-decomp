/* func_ov004_02227958 @ 0x02227958, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(int a, int b);
extern void func_020109fc(void *self, int a, int b, int c);
extern int data_020ccf94;
void func_ov004_02227958(unsigned char *self, void *message, int previous)
{
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        if (*(int *) (self + 0x704) != 0x3e) {
            func_020109fc(self, 0x3e, 3, 0);
        }
    } else {
        func_020109fc(self, 0, 3, 3);
    }
}
