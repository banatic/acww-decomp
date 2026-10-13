/* func_020bc5c4 @ 0x020bc5c4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bca80(void *p, int a, int b, int c);
extern void func_020bc9c4(void *p, int a);
extern void func_020bcce4(void *p);

void func_020bc5c4(void *p)
{
    int i;
    i = *(int *) ((char *) p + 0x2f30);
    if (i < 0) {
        func_020bca80(p, 0, 0x64, 0);
    } else if (i == 0) {
        func_020bc9c4(p, 0x10);
    }
    func_020bcce4(p);
}
