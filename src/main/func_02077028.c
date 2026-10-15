/* func_02077028 @ 0x02077028, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_020736bc(unsigned int *param1, unsigned int *param2, int param3);
extern void func_02052a64(int param1, unsigned int *param2);

void func_02077028(int param1, int param2, int param3, unsigned int player)
{
    unsigned int local_4;
    unsigned int *ptr;
    int r4;

    r4 = param3;
    ptr = (unsigned int *) data_020ccf94;
    func_020736bc(ptr, &local_4, 4);
    func_02052a64(r4, &local_4);
}
