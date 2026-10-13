/* func_0207892c @ 0x0207892c, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073d90(int);
extern void func_02078a0c(void *, int, int);
extern void func_02073820(int);
extern void func_020737f0(int, void *, int);
extern void func_02073770(int, int, int);

void func_0207892c(int a, int b)
{
    int local;
    int handle;
    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }
    func_02078a0c(&local, a, b);
    handle = data_020ccf94;
    func_02073820(handle);
    func_020737f0(handle, &local, 1);
    func_02073770(handle, 0x37, 4);
}
