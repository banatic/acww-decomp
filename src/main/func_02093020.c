/* func_02093020 @ 0x02093020, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094bcc(int arg0, int arg1, int *arg2);

void func_02093020(int param0)
{
    int local[3];
    local[0] = 0;
    local[1] = 0;
    local[2] = 0x1000;
    func_02094bcc(param0, 0, local);
}
