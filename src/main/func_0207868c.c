/* func_0207868c @ 0x0207868c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *obj);
extern void func_020786f8(int *dst, int a, int b, int c);
extern void func_02073820(void *obj);
extern void func_020737f0(void *obj, int *buf, int size);
extern void func_02073770(void *obj, int a, int b);
extern void *data_020ccf94;

void func_0207868c(int arg1, int arg2, int arg3)
{
    int local[2];
    void *p;
    if (func_02073d90(data_020ccf94)) {
        func_020786f8(local, arg1, arg3, arg2);
        p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, local, 2);
        func_02073770(p, 0x3c, 4);
    }
}
