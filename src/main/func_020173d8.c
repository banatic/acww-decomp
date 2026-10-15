/* func_020173d8 @ 0x020173d8, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(void *, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_0209129c(int);
extern void func_02091278(int, void *, void *, int);

void func_020173d8(void *a, void *b)
{
    int field;

    if (func_020164cc((char *) b + 0x334, (int) b) != 0) {
        func_02016764((char *) b + 0x334, b, 0x2a, 0, 1, 0x1000, 0, 0);
        field = *(int *) ((char *) a + 0xac);
        if (field != -1) {
            func_0209129c(field);
        }
        ((char *) a)[0x98] = 1;
    } else {
        field = *(int *) ((char *) a + 0xac);
        if (field != -1) {
            func_02091278(field, (char *) b + 0x478, (char *) b + 0x8e, 0);
        }
    }
}