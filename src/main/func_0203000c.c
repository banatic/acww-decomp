/* func_0203000c @ 0x0203000c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202ff68(int, void *, void *);
extern int func_020ea9e4(void *, void *);

int func_0203000c(int a, void *b)
{
    char buffer[16];
    func_0202ff68(a, buffer, b);
    return func_020ea9e4(buffer, b);
}
