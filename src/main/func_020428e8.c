/* func_020428e8 @ 0x020428e8, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_02042a08(void *, void *, char *, int);
extern unsigned int func_020644cc(unsigned int);
extern void func_02042954(void *, unsigned int, void *, void *, int, void *);
extern void func_020429a0(void *, char *, void *, int);
extern void *MI_CpuFill8(void *, int, unsigned int);
extern void *MI_CpuCopy8(void *, const void *, unsigned int);
extern char data_020db87c;

void func_020428e8(void *p0, char *p1, void *p2)
{
    unsigned int result;
    char tmp[8];
    char buffer[0x54];

    result = func_02042a08(p0, buffer, p1 + 0x1726a, 0x54);
    if (result == 0) {
        result = 0x54;
        MI_CpuFill8(buffer, 0, result);
    }
    result = func_020644cc(result);
    MI_CpuCopy8(p2, tmp, 8);
    func_02042954(p0, result, &data_020db87c, buffer, 0x54, tmp);
    func_020429a0(p0, p1 + 0x1726a, buffer, 0xb);
}
