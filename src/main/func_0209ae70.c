/* func_0209ae70 @ 0x0209ae70, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209af04(void *arg0);
extern void func_0209bd30(void *s, unsigned char a, unsigned short *h, unsigned char b);
extern void func_0209bc24(int p1, int p2);
extern void func_02003728(void *a, void *b);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void func_0209ae70(unsigned int param1, unsigned int param2, unsigned int param3)
{
    unsigned short local_0;
    func_0209af04((void *) param1);
    local_0 = 0xfff1;
    func_0209bd30((void *) (param1 + 0x10), 0x15, &local_0, 0);
    func_0209bc24((int) (param1 + 0x10), 0);
    func_02003728((void *) param1, (void *) param2);
    MI_CpuCopy8((const void *) param3, (void *) (param1 + 0x1c), 8);
}
