/* func_02001aac @ 0x02001aac, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void G2x_SetBlendBrightness_(unsigned int addr, unsigned int size, unsigned int data);
extern void G2x_SetBlendBrightnessExt_(unsigned int addr, unsigned int arg1, unsigned int arg2, unsigned int arg3,
                                       unsigned int arg4, unsigned int arg5);

void func_02001aac(unsigned int param)
{
    if (param != 0) {
        G2x_SetBlendBrightness_(0x04000050, 0x3f, param);
        G2x_SetBlendBrightness_(0x04001050, 0x3f, param);
    } else {
        G2x_SetBlendBrightnessExt_(0x04000050, 0x1f, 0x20, 0x10, 0x10, param);
        G2x_SetBlendBrightnessExt_(0x04001050, 0x1f, 0x20, 0x10, 0x10, param);
    }
}
