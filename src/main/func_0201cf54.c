/* func_0201cf54 @ 0x0201cf54, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0201cf54(int *base)
{
    int i = 0;
    int v = i;
    for (; i < 5; i++) {
        *(base + i + 0x50) = v;
    }
}
