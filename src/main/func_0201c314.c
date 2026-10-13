/* func_0201c314 @ 0x0201c314, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200322c(void *a, void *b);

int func_0201c314(void *r0, void *r1)
{
    int result = 0;
    if (r1 != 0) {
        result = func_0200322c((char *) r0 + 0x5c, (char *) r1 + 0x5c);
    }
    return result;
}
