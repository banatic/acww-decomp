/* func_02065ba0 @ 0x02065ba0, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020edf70(int);
extern int func_020ee660(void);
extern int func_02065bec(void);
extern int func_02064d8c(void);
extern int __cxa_vec_ctor(int, int, int, int, int);
extern int data_020da13c;
extern int data_020de710;

int func_02065ba0(void)
{
    int *r4;
    int r0;

    r4 = (int *) func_020edf70(0x17c);
    if (r4 != 0) {
        func_020ee660();
        *r4 = (int) &data_020da13c;
        *r4 = (int) &data_020de710;
        __cxa_vec_ctor((int) (r4 + 0x16), 3, 0x44, (int) &func_02065bec, (int) &func_02064d8c);
    }
    return (int) r4;
}
