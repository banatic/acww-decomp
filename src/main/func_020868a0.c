/* func_020868a0 @ 0x020868a0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003750(char *ptr);
extern int func_0209526c(char *ptr);

char *func_020868a0(char *ptr)
{
    func_02003750(ptr + 0x2e);
    func_02003750(ptr + 0x1e);
    func_0209526c(ptr);
    return ptr;
}
