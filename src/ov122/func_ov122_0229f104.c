/* func_ov122_0229f104 @ 0x0229f104, 0x4c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *p);
extern int func_ov002_02208ad8(void *p, unsigned char c);
extern int func_ov002_0220a08c(void *p, int a, int b, int c);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov122_0229f104(unsigned char *arg)
{
    int a = func_ov002_02208ae4(arg + 0x42b0);
    int b = func_ov002_02208ad8(arg + 0x42b0, arg[0xb6]);
    func_ov002_0220a08c(arg + 0x4058, a, b, 2);
    arg[0xb4] = 0x14;
    func_ov002_02208098((void *) (arg), 7);
}
