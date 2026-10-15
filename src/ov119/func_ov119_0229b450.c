/* func_ov119_0229b450 @ 0x0229b450, 0x4c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208d30(void *ptr, int value);
extern int func_ov002_02208d4c(void *ptr, int value1, int value2);
extern void func_ov119_0229a50c(void *ptr, int value);
extern void func_ov119_0229a410(void *ptr, int value);

void func_ov119_0229b450(char *obj)
{
    func_ov002_02208d30(obj + 0x4c4, 0xa);
    func_ov002_02208d4c(obj + 0x4c4, 0xd3, 0xa);
    func_ov002_02208d4c(obj + 0x4c4, 4, 1);
    func_ov002_02208d4c(obj + 0x4c4, 0x13, 0xa);
    func_ov119_0229a50c(obj, 1);
    func_ov119_0229a410(obj, 0x10);
}
