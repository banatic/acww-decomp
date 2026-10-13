/* func_0207889c @ 0x0207889c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *p);
extern void func_02078a0c(void *out, int a, int b);
extern void func_02073820(void *p);
extern void func_020737f0(void *p, void *q, int r);
extern void func_02073770(void *p, int a, int b);

extern void *data_020ccf94;

void func_0207889c(int a, int b, int c, int d)
{
    if (func_02073d90(data_020ccf94) != 0) {
        int local;
        void *p;
        func_02078a0c(&local, a, b);
        p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, &local, 1);
        func_020737f0(p, &c, 1);
        func_02073770(p, 0x38, 4);
    }
}
