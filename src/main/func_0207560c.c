/* func_0207560c @ 0x0207560c, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(void *dst, const void *src, unsigned int size);
extern char *func_02090040(int param);
extern void func_02090174(char *param);
extern int func_020b65c4(void);
extern int func_020a132c(void);
extern void func_020a242c(int param1, int param2, int param3);

void func_0207560c(char *a, int b, int c)
{
    if (b != 0) {
        int local;
        char *val;
        MI_CpuCopy8(a, &local, 4);
        val = func_02090040(c);
        MI_CpuCopy8(a + 4, val + local, b - 4);
    } else {
        func_02090174(func_02090040(c));
    }
    if (func_020b65c4() == 13 || func_020b65c4() == 47) {
        if (func_020a132c() != 0) {
            func_020a242c(func_020a132c(), c, 1);
        }
    }
}
