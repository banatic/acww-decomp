/* func_ov122_0229f034 @ 0x0229f034, 0x54 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8874(void *object, const void *source, int length);
extern int func_020a8a70(char *p1, char *p2, int a, int b);
extern int func_020b4424(char *p);
extern int func_020a87e0(char *p1, char *p2);
extern int func_0205182c(char *p1, int a, int b);

void func_ov122_0229f034(char *base, int a, int b)
{
    func_020a8874(base + 0x4150, (const void *) a, b);
    func_020a8a70(base + 0x40bc, base + 0x4150, 0, 0);
    if (func_020b4424(base + 0x40bc) != 0) {
        func_020a87e0(base + 0x4150, base + 0x40bc);
        func_0205182c(base + 0x4150, a, b);
    }
}
