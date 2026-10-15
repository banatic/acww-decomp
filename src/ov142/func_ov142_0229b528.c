/* func_ov142_0229b528 @ 0x0229b528, 0x34 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;

void func_ov142_02299830(unsigned int arg);
void func_ov142_02299908(unsigned int arg);
unsigned char *func_ov002_02208098(void *object, unsigned char value);
void func_ov142_0229aec4(unsigned int arg);

void func_ov142_0229b528(unsigned int arg)
{
    if (data_021fbe40 & 1) {
        func_ov142_02299830(arg);
    } else {
        func_ov142_02299908(arg);
        func_ov002_02208098((void *) (arg), 4);
        func_ov142_0229aec4(arg);
    }
}
