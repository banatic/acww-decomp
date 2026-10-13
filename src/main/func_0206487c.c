/* func_0206487c @ 0x0206487c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02064cd8(void *dst, const void *src);
extern int func_020648a0(void *ptr);
extern void FS_CloseFile(void *ptr);

int func_0206487c(void *src)
{
    char buf[0x48];
    int result;

    func_02064cd8(buf, src);
    result = func_020648a0(buf);
    FS_CloseFile(buf);
    return result;
}
