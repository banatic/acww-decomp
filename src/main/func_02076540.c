/* func_02076540 @ 0x02076540, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_020736bc(unsigned int *param0, unsigned char *param1, int param2);
extern void func_020a6f74(unsigned int param0, unsigned char param1);

void func_02076540(unsigned int param0, unsigned int param1, unsigned int param2, unsigned int param3)
{
    unsigned int *ptr;
    unsigned char byte;
    unsigned int local;

    ptr = (unsigned int *) data_020ccf94;
    func_020736bc(ptr, (unsigned char *) &byte, 1);
    func_020a6f74(param3, byte);
}
