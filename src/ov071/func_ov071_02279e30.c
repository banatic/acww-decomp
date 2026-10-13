/* func_ov071_02279e30 @ 0x02279e30, 0x60 bytes, Thumb, module ov071
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *p);
extern void func_0201c280(void *a, void *b);
extern void func_ov071_02278f1c(void *a, void *b);
extern void func_0201af28(void *a, int b, int c, int d, int e);
extern void MI_CpuFill8(void *dest, unsigned char data, unsigned int size);

int func_ov071_02279e30(char *p)
{
    if (!func_0202edc8(p)) {
        return 0;
    }
    func_0201c280(p, p + 0x658);
    func_ov071_02278f1c(p + 0x658, p);
    func_0201af28(p + 0x350, 2, 0x200, 0x100, 0x100);
    MI_CpuFill8(p + 0x724, 0, 5);
    return 1;
}
