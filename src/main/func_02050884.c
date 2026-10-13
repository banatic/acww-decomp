/* func_02050884 @ 0x02050884, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void (*data_020dcefc[3])(void *, int);

void func_02050884(void *p, int arg)
{
    unsigned char b = *(unsigned char *) p;
    if (b >= 3) {
        return;
    }
    data_020dcefc[b](p, arg);
}
