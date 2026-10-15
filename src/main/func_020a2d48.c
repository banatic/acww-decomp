/* func_020a2d48 @ 0x020a2d48, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021dc7aa;
extern char data_021dc7a8;
extern char data_021dc7bc;

extern void func_02074b44(int a, int b, int c);
extern void func_020742fc(void);
extern void *func_020642a4(void *p);
extern void MI_CpuCopy8(void *dest, void *src, int n);
extern int func_0209f180(void *p);
extern void func_020730c8(void);
extern int func_020eb9f0(void *p, int n);
extern unsigned char func_0209877c(void *p);

void func_020a2d48(unsigned char *param)
{
    unsigned char local[16];
    void *ret;

    *(unsigned short *) (param + 0xd0) = 0x258;
    func_02074b44(1, 2, 0);
    func_020742fc();
    ret = func_020642a4(&data_021dc7aa);
    MI_CpuCopy8(ret, local, 12);
    local[0xd] = 1;
    local[0xc] = 0;
    if (func_0209f180(&data_021dc7a8) == 0) {
        local[0xc] = 1;
    }
    func_020730c8();
    func_020eb9f0(local, 14);
    param[0x102] = func_0209877c(&data_021dc7bc);
}
