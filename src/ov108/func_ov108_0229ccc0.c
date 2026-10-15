/* func_ov108_0229ccc0 @ 0x0229ccc0, 0x4c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov108_0229cb54(void *a, void *b);
extern int func_ov108_0229cc5c(void *a, void *b);
extern int func_02066830(void *dst, int val);
extern void func_ov108_0229cc90(void *a, unsigned char b, void *c);
extern void func_ov108_0229c8a4(void *a, void *b);

int func_ov108_0229ccc0(void *param1, void *param2)
{
    if (func_ov108_0229cb54(param1, param2) == 0) {
        func_02066830((char *) param1 + 0x1AC, func_ov108_0229cc5c(param1, param2));
        func_ov108_0229cc90(param1, ((unsigned char *) param1)[0x2AF], (char *) param1 + 0x1AC);
    }
    func_ov108_0229c8a4(param1, param2);
    return 1;
}
