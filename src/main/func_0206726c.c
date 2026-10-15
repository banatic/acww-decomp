/* func_0206726c @ 0x0206726c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206d63c(void *ptr);
extern int func_02067344(void *p, int a, int b);
extern int func_020a9a08(void *ptr, int ret);
extern int func_020a9938(void *ptr, int val);
extern int func_020a9530(void *ptr);
extern void func_020a82bc(void *ptr, int ret);
extern void func_020a99d8(void *ptr);

void func_0206726c(void *p)
{
    int ret;
    func_0206d63c((char *) p + 0xb14);
    ret = func_02067344(p, 0, 0);
    if (func_020a9a08((char *) p + 0xb14, ret)) {
        func_020a9938((char *) p + 0xb14, *(int *) ((char *) p + 0x14a8) + 0x1e);
    }
    ret = func_020a9530((char *) p + 0xb14);
    func_020a82bc((char *) p + 0x14ac, ret);
    func_020a99d8((char *) p + 0xb14);
}
