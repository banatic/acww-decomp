/* func_ov003_0221a228 @ 0x0221a228, 0x1c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

int func_ov003_0221a228(void *base)
{
    unsigned short *p = (unsigned short *) ((char *) base + 0x378);
    unsigned short v;

    v = *p;
    v &= ~0x10;
    *p = v;

    v = *p;
    v |= 0x20;
    *p = v;

    return 1;
}
