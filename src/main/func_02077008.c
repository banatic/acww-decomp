/* func_02077008 @ 0x02077008, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_020736bc(unsigned int, unsigned int *, unsigned int);
extern void func_02052960(unsigned int *);

void func_02077008(unsigned int arg)
{
    unsigned int local;
    func_020736bc(data_020ccf94, &local, arg);
    func_02052960(&local);
}
