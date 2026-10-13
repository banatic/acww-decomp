/* func_0200f1a4 @ 0x0200f1a4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02096484(void *, int, int);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);

void func_0200f1a4(int unused, int a, int b)
{
    int local;
    void *obj;

    if (func_02073d90(data_020ccf94)) {
        func_02096484(&local, b, a);
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &local, 3);
        func_02073770(obj, 0x2b, 4);
    }
}
