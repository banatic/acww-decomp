/* func_ov070_02279a50 @ 0x02279a50, 0x40 bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *p);
extern void func_0201c280(char *p, char *q);
extern void func_ov070_02279654(char *p, char *q);
extern void MI_CpuFill8(char *p, int value, int len);

int func_ov070_02279a50(char *p)
{
    if (func_0202edc8(p) == 0) {
        return 0;
    }

    func_0201c280(p, p + 0x658);
    func_ov070_02279654(p + 0x658, p);
    MI_CpuFill8(p + 0x724, 0, 0x14);
    return 1;
}
