/* func_0207880c @ 0x0207880c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_02073d90(void *);
extern void func_02078a0c(int *, int, int);
extern void func_02073820(void *);
extern void func_020737f0(void *, void *, int);
extern void func_02073770(void *, int, int);

void func_0207880c(int a, int b, int c, int d)
{
    if (func_02073d90(data_020ccf94)) {
        int temp;
        void *obj;

        func_02078a0c(&temp, a, b);
        obj = data_020ccf94;
        func_02073820(obj);
        func_020737f0(obj, &temp, 1);
        func_020737f0(obj, &c, 1);
        func_02073770(obj, 0x39, 4);
    }
}
