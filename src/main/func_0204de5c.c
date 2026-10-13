/* func_0204de5c @ 0x0204de5c, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c80e0[5];
extern void func_0204dd78(int);
extern void func_0204dc9c(int, int);
extern void func_020e993c(int, int);
extern void func_0205c0f0(void);

void func_0204de5c(int param0)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (data_021c80e0[i] != 0) {
            func_0204dd78(data_021c80e0[i]);
            func_0204dc9c(data_021c80e0[i], param0);
            func_020e993c(param0, data_021c80e0[i]);
            data_021c80e0[i] = 0;
        }
    }
    func_0205c0f0();
}
