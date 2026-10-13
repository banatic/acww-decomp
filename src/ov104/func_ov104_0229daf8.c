/* func_ov104_0229daf8 @ 0x0229daf8, 0x38 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov104_0229d4a8(void);
extern int func_ov104_0229d8a8(void *a, void *b);
extern int func_ov104_0229d858(void *a, void *b);
extern void func_ov104_0229db74(void *a, void *b, int c);

void func_ov104_0229daf8(void *a, void *b, void *c)
{
    func_ov104_0229d4a8();
    *(int *) ((char *) a + 0xa8) = func_ov104_0229d8a8(a, b);
    *(int *) ((char *) a + 0xac) = func_ov104_0229d858(a, b);
    func_ov104_0229db74(a, c, 4);
}
