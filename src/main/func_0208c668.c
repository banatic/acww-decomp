/* func_0208c668 @ 0x0208c668, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a144(void *ptr);

void func_0208c668(void *p)
{
    int i;
    char *base;
    int stride;

    i = 0;
    base = (char *) p;
    base += 0xc;
    stride = 20;

    do {
        func_0208a144(base + i * stride);
        i++;
    } while (i < 9);
}
