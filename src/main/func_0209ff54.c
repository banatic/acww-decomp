/* func_0209ff54 @ 0x0209ff54, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f3278;
extern int data_020e3800;
extern int data_020e3bf0;

extern int func_02088208(void *);
extern int func_020881ac(void *);
extern int func_020508fc(void *, int, int);
extern void func_020881b8(void *, int);
extern void func_02073100(void);
extern int func_020eb384(void *, void *, int, int);

int func_0209ff54(void)
{
    void *work;
    int v1, v2, val;

    work = &data_021f3278;
    if (func_02088208(work) == 3) {
        v1 = func_020881ac(work);
        v2 = func_020508fc(work, 0x238, v1);
        func_020881b8(work, v2);
        val = data_020e3800;
        func_02073100();
        func_020eb384(&data_020e3bf0, work, 0x238, val);
        return 1;
    }
    return 0;
}
