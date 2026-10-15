/* func_ov106_0229c910 @ 0x0229c910, 0x48 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov106_0229c9dc(void *self);
extern void func_ov106_0229c47c(void *self);
extern void func_ov106_0229c3a8(void *self);
extern void func_ov106_0229c3a0(unsigned int argument0);
extern void func_ov106_0229d73c(void *self);

void func_ov106_0229c910(void *self)
{
    switch (((unsigned char *) self)[0xbc]) {
        case 0:
            func_ov106_0229c9dc(self);
            break;
        case 1:
            func_ov106_0229c47c(self);
            break;
        case 2:
            func_ov106_0229c3a8(self);
            break;
        case 3:
            func_ov106_0229c3a0((unsigned int) self);
            break;
        case 4:
        default:
            func_ov106_0229d73c(self);
            break;
    }
}
