/* func_ov003_0222d1bc @ 0x0222d1bc, 0x3c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern char data_ov003_02260794[0x200];
extern char data_ov003_02260594[0x200];

void func_ov003_0222d1bc(void *dst, int kind)
{
    switch (kind) {
        case 0:
        case 5:
        case 6:
            MI_CpuCopy8(data_ov003_02260794, dst, 0x200);
            break;
        default:
            MI_CpuCopy8(data_ov003_02260594, dst, 0x200);
            break;
    }
}
