/* func_ov122_0229f454 @ 0x0229f454, 0x14 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov122_0229efd8(void *param, unsigned int flags);

void func_ov122_0229f454(void *param, unsigned char value)
{
    ((unsigned char *) param)[0xB3] = value;
    func_ov122_0229efd8(param, 0x800);
}
