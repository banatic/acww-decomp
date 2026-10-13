/* func_02095b64 @ 0x02095b64, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02095ba8(unsigned short *param0, int param1, int param2);

void func_02095b64(void)
{
    unsigned short local;
    unsigned short *ptr;

    local = 0xFFF1;
    ptr = &local;
    func_02095ba8(ptr, 3, 5);
}
