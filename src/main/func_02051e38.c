/* func_02051e38 @ 0x02051e38, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *ptr);
extern int func_02073918(void *ptr, int arg);
extern int func_0205340c(void *addr, int param);
extern void func_02073820(void *ptr);
extern void func_02073770(void *ptr, int a, int b);

extern int data_021c8750;
extern void *data_020ccf94;
extern int data_021c87fc;

void func_02051e38(int param)
{
    void *ptr;
    void *ptr2;

    data_021c8750 = 0;
    ptr = data_020ccf94;
    if (func_02073d90(ptr) == 0) {
        goto else_branch;
    }
    if (func_02073918(ptr, 0) != 0) {
        goto else_branch;
    }
    if (func_02073918(ptr, 4) == 0) {
        goto then_branch;
    }
else_branch:
    func_0205340c(&data_021c87fc, param);
    goto end;
then_branch:
    ptr2 = data_020ccf94;
    func_02073820(ptr2);
    func_02073770(ptr2, 0x21, 0);
end:;
}
