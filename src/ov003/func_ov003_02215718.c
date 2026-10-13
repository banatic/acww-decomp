/* func_ov003_02215718 @ 0x02215718, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109fc(int, int, int, int);
extern void func_0205eae0(int, int, int, int);
extern int func_02073908(int, int);
extern void func_02035684(int, int, int);
extern int data_020ccf94;

void func_ov003_02215718(int a0)
{
    func_020109fc(a0, 0x55, 3, 0);
    func_0205eae0(a0 + 0x5a0, 0x18, 3, 0);
    if (func_02073908(data_020ccf94, *(int *) (a0 + 0x800)) != 0) {
        func_02035684(0x12, 0, 0);
    }
}
