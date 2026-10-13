/* func_ov102_0229d320 @ 0x0229d320, 0x5c bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov102_0229d464(void *a, int b);
extern int func_ov102_0229d454(void *a, int b);
extern int func_ov102_0229d034(void *a, int b);
extern int func_ov102_0229cff8(void *a, int b);
extern void func_ov102_0229d2a4(void *a, unsigned char b, int c, int d);
extern void func_ov102_0229cc60(void *a, int b);

int func_ov102_0229d320(void *a, int b)
{
    if (func_ov102_0229d464(a, b) != 0 || func_ov102_0229d454(a, b) != 0) {
        int r6 = func_ov102_0229d034(a, b);
        if (r6 != 0xfff1) {
            int r3 = func_ov102_0229cff8(a, b);
            unsigned char byte = ((unsigned char *) a)[0x25a2];
            func_ov102_0229d2a4(a, byte, r6, r3);
        }
        func_ov102_0229cc60(a, b);
        return 1;
    } else {
        return 0;
    }
}
