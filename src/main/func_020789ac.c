/* func_020789ac @ 0x020789ac, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02078a0c(void *, int, int);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);

void func_020789ac(int arg0, int arg1)
{
    int local;
    void *p;
    if (func_02073d90(data_020ccf94) != 0) {
        func_02078a0c(&local, arg0, arg1);
        p = data_020ccf94;
        func_02073820(p);
        func_020737f0(p, &local, 1);
        func_02073770(p, 0x36, 4);
    }
}
