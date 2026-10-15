/* func_020b3598 @ 0x020b3598, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void NNS_G3dMdlSetMdlAlpha(void *a, int b, int c);

void func_020b3598(signed char *str, void *arg1, int r2)
{
    signed char ch = *str;
    if (ch == -1) {
        return;
    }
    NNS_G3dMdlSetMdlAlpha(arg1, ch, (unsigned char) (((r2 * 29) >> 12) + 1));
}
