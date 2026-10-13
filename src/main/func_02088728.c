/* func_02088728 @ 0x02088728, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209df64(unsigned int);
extern void MI_CpuCopy8(unsigned int, unsigned int, int);

void func_02088728(unsigned int arg0, unsigned int arg1)
{
    unsigned int local_0;
    unsigned int r5;
    unsigned int r4;

    r5 = arg0;
    r4 = arg1;
    func_0209df64(r5 + 1);
    MI_CpuCopy8(r4, r5, 1);
    return;
}
