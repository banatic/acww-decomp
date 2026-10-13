/* func_0200b374 @ 0x0200b374, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *s);
extern int func_02056f28(void *ptr, int n);
extern void func_0200f328(void *s, int n);

void func_0200b374(void *s)
{
    func_02010f5c(s);
    if (*(int *) ((char *) s + 0x704) == 22) {
        if (func_02056f28((char *) s + 0x2d0, 9) != 0) {
            func_0200f328(s, 79);
        }
    }
}
