/* func_ov100_0229cb80 @ 0x0229cb80, 0x54 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ae4(void *ptr);
extern int func_ov002_02208ad8(void *ptr, unsigned char byte);
extern void func_ov002_0220a08c(void *ptr, int a, int b, int c);
extern void func_ov002_02208098(void *ptr, int val);

void func_ov100_0229cb80(unsigned char *param)
{
    int v1;
    v1 = func_ov002_02208ae4(param + 0x22d8);
    func_ov002_0220a08c(param + 0x2274, v1, func_ov002_02208ad8(param + 0x22d8, param[0x2926]), 2);
    param[0x2924] = param[0x8d];
    func_ov002_02208098(param, 8);
}
