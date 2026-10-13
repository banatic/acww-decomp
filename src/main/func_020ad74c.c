/* func_020ad74c @ 0x020ad74c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern int func_020ad798(void);
extern int func_02073d90(int);
extern void func_020aea84(void);
extern void func_020af3a0(void *, int);
extern void func_020ad78c(int);

extern int data_020ccf94;
extern int data_021f395c;

void func_020ad74c(void)
{
    if (func_020b6660() != 0) {
        if (func_020ad798() == 2) {
            if (func_02073d90(data_020ccf94) == 0) {
                func_020aea84();
                func_020af3a0(&data_021f395c, 0);
            }
        }
        func_020ad78c(0);
    }
}
