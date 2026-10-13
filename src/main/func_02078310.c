/* func_02078310 @ 0x02078310, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *obj);
extern void func_02078380(void *dest, void *src1, void *src2);
extern void func_02073820(void *obj);
extern void func_020737f0(void *obj, void *buf, int len);
extern void func_02073770(void *obj, int a, int b);

void func_02078310(void *arg0, void *arg1)
{
    int local[3];
    if (func_02073d90(data_020ccf94) == 0) {
        return;
    }
    if (arg1 == 0) {
        return;
    }
    func_02078380(local, arg0, arg1);
    {
        void *obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, local, 9);
        func_02073770(obj, 0x3b, 4);
    }
}
