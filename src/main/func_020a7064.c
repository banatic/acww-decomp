/* func_020a7064 @ 0x020a7064, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a74bc(void);
extern void func_02073820(int);
extern int func_020733c4(int);
extern int func_02073394(int);
extern void func_020737f0(int, int, int);
extern void func_02073770(int, int, int);
extern void func_020733ac(int);
extern int data_020ccf94;

void func_020a7064(int param)
{
    int obj;
    int tmp1;
    int tmp2;
    func_020a74bc();
    obj = data_020ccf94;
    func_02073820(obj);
    tmp1 = func_020733c4(obj);
    tmp2 = func_02073394(obj);
    func_020737f0(obj, tmp1, tmp2);
    func_02073770(obj, 0x10, param);
    func_020733ac(obj);
}
