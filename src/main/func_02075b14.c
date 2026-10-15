/* func_02075b14 @ 0x02075b14, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073044(void);
extern int func_020ebf70(void);
extern int func_02077a8c(int);
extern int *data_020ccf94;
extern int func_02073918(int *, int);
extern int func_02073d28(int *, int);
extern void func_02077b3c(int, int, int);
extern void func_0209e474(int *);
extern void MI_CpuCopy8(int *, int, int);
extern int func_02073e30(int *, int, int, int, int, int, int, int, int, int);

int func_02075b14(int arg)
{
    int *ptr;
    int val, temp;
    int local[2];

    if ((func_02073044(), func_020ebf70()) != 0 && func_02077a8c(arg) != 0) {
        ptr = data_020ccf94;
        func_02073918(ptr, 0);
        val = func_02073d28(ptr, 4);
        func_02077b3c(val, 0, 10);
        local[0] = 0;
        local[1] = 0;
        func_0209e474(local);
        MI_CpuCopy8(local, val + 1, 8);
        temp = func_02073d28(ptr, 4);
        return func_02073e30(ptr, temp, 9, arg, 0, 0, 0, 0, 0, 0);
    }
    return 0;
}
