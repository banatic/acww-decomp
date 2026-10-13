/* func_ov147_0229a420 @ 0x0229a420, 0x20 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *, unsigned int);
extern void func_02112ba8(void *, unsigned char, unsigned int);

void func_ov147_0229a420(void *arg)
{
    DC_FlushRange(arg, 0x9e0);
    func_02112ba8(arg, 0, 0x9e0);
}
