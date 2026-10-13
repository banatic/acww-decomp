/* func_ov099_0229c994 @ 0x0229c994, 0x3c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229c2ac(void *, int);
extern void func_ov094_0229a6bc(void *, int, int);

void func_ov099_0229c994(void *s)
{
    unsigned char b;
    if (func_ov099_0229c2ac(s, 0x40) != 0) {
        return;
    }
    b = *(unsigned char *) ((char *) s + 0x2903);
    if ((b != 0) && (b == 2)) {
        func_ov094_0229a6bc((char *) s + 0xcc, *(int *) ((char *) s + 0x27f8), *(int *) ((char *) s + 0x27fc));
    }
}
