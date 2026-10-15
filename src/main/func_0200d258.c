/* func_0200d258 @ 0x0200d258, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200d1a0(void *p, int a, int b, int c);
extern int DWC_Alloc(int a, int b);
extern int func_02096518(int *out, int a, int b);

void func_0200d258(void *p, const unsigned char *q)
{
    int st;

    if (*q) {
        func_0200d1a0(p, 0, 1, -1);
    }
    if (*(int *) ((char *) p + 0x7f8) == 0) {
        if (DWC_Alloc(0x1b, 4)) {
            *(int *) ((char *) p + 0x7f8) = 1;
        } else if (func_02096518(&st, -1, *(int *) ((char *) p + 0x800))) {
            if (st == 2 || st == 0x40) {
                *(int *) ((char *) p + 0x7f8) = 1;
            }
        }
    }
}
