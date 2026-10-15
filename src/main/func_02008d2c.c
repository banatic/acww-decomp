/* func_02008d2c @ 0x02008d2c, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02008da8(void *param1, void *param2);
extern int func_02008dc0(void *param1, int param2, int param3, void *param4);

void func_02008d2c(void *param1, void *param2)
{
    int sp_value;
    void *temp;

    func_02008da8((char *) param1 + 0x8f0, &sp_value);
    temp = param1;
    func_02008dc0(temp, *(short *) &sp_value, 6, param2);
}
