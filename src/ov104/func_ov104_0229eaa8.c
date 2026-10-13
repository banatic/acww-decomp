/* func_ov104_0229eaa8 @ 0x0229eaa8, 0xa0 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229af40(void *ptr, int arg);
extern void func_ov094_0229bbd8(void *ptr, int arg);
extern void func_ov094_0229a2b0(void *ptr, int arg);
extern void func_ov002_02209e18(void *ptr);
extern void func_ov002_02209984(void *ptr, int arg1, int arg2, int arg3);
extern void func_0206e2ec(void *ptr, int arg);
extern void func_02066650(void *ptr);
extern void func_ov104_0229cb38(void *ptr);

void func_ov104_0229eaa8(unsigned char *p)
{
    int i;

    *(int *) (p + 0x94) = 0;
    func_ov094_0229af40(p + 0x2f8, 2);
    func_ov094_0229bbd8(p + 0xd58, 1);
    func_ov094_0229a2b0(p + 0xd80, 6);
    *(unsigned char *) (p + 0xb6) = 0x21;
    func_ov002_02209e18(p + 0x2488);
    *(unsigned char *) (p + 0xb4) = 0;
    *(unsigned char *) (p + 0xb8) = 0x0b;
    func_ov002_02209984(p + 0x2504, 3, 0, 0);
    func_0206e2ec(p + 0x2a14, 3);
    for (i = 0; i < 10; i++) {
        func_02066650(p + 0x2db4 + i * 0x100);
    }
    func_ov104_0229cb38(p);
    *(unsigned char *) (p + 0xbf) = 0;
}
