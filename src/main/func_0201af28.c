/* func_0201af28 @ 0x0201af28, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0201af28(int *base, int index, int a, int b, int c)
{
    char *p;
    if (index < 1 || index >= 3) {
        return;
    }
    p = (char *) base + 12;
    p += index * 12;
    *(int *) p = a;
    *(int *) (p + 4) = b;
    *(int *) (p + 8) = c;
}
