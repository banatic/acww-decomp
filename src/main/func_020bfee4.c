/* func_020bfee4 @ 0x020bfee4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */
extern void func_020bfd1c(void *);
extern void func_020bfe6c(void *);

void func_020bfee4(void *p0)
{
    int v;
    int match;

    *(int *) ((char *) p0 + 0x64) += 1;
    v = *(int *) ((char *) p0 + 0xc);
    match = 0;
    v -= 0x21;
    if ((unsigned int) v <= 9) {
        if ((0x249 & (1 << v)) != 0) {
            match = 1;
        } else {
            match = 0;
        }
    }
    if (match != 0) {
        func_020bfd1c(p0);
    } else {
        func_020bfe6c(p0);
    }
}
