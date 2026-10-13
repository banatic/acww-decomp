/* func_0205fa40 @ 0x0205fa40, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0205fa84(int arg);
extern int func_02073d90(void *p);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, int a, int b);
extern void func_02073770(void *p, int a, int b);
extern int *data_020ccf94;

void func_0205fa40(int arg)
{
    if (func_0205fa84(arg) && func_02073d90(data_020ccf94)) {
        int *p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, arg, 5);
        func_02073770(p, 0x12, 4);
    }
}
