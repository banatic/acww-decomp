/* func_02074078 @ 0x02074078, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_020732c0(void *param1);
extern void func_020732cc(void *param1, int param2);

void func_02074078(void)
{
    unsigned int *r4;
    int r0;
    int r1;

    r4 = (unsigned int *) data_020ccf94;
    r0 = func_020732c0(r4);
    r1 = r0;
    if ((r0 & 0x40) == 0) {
        r1 = r0 | 0x40;
        func_020732cc(r4, r1);
    }
}
