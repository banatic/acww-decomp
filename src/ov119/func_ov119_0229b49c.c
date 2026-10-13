/* func_ov119_0229b49c @ 0x0229b49c, 0x74 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208d30(void *base, int a);
extern void func_ov002_02208d4c(void *base, int a, int b);
extern int func_ov119_0229ae28(void *obj);
extern void func_02077c3c(void);
extern int func_02077d6c(void);
extern void func_ov119_0229a50c(void *obj, int a);

void func_ov119_0229b49c(void *obj)
{
    func_ov002_02208d30((char *) obj + 0x4c4, 0xa);
    func_ov002_02208d4c((char *) obj + 0x4c4, 0xcf, 3);
    func_ov002_02208d4c((char *) obj + 0x4c4, 0xd0, 2);
    if (func_ov119_0229ae28(obj)) {
        func_02077c3c();
        if (func_02077d6c() == 0) {
            func_ov002_02208d4c((char *) obj + 0x4c4, 0xd1, 4);
        }
    }
    func_ov002_02208d4c((char *) obj + 0x4c4, 0xd2, 0);
    func_ov002_02208d4c((char *) obj + 0x4c4, 2, 0xa);
    func_ov119_0229a50c(obj, 0);
}
