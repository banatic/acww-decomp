/* func_0206e1d8 @ 0x0206e1d8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02051bf8(void *p, int n);
extern void func_02065f4c(void *dst, void *src);
extern void *func_02051c8c_unk(void *p, int n);
extern void *func_02051d08(void *p, int n);

void func_0206e1d8(void *self, void *other)
{
    func_02051bf8((char *) self + 0x2b8, 0x28);
    func_02065f4c(other, (char *) self + 0x2b8);
    *(void **) ((char *) self + 0x320) = func_02051c8c_unk((char *) self + 0x2b8, 0x28);
    *(void **) ((char *) self + 0x324) = func_02051d08((char *) self + 0x2b8, 0x28);
}
