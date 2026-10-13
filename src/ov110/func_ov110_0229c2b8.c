/* func_ov110_0229c2b8 @ 0x0229c2b8, 0xe bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

void func_ov110_0229c2b8(void *r0, unsigned int r1)
{
    unsigned int *p;
    unsigned int v;

    p = (unsigned int *) ((char *) r0 + 0x94);
    v = *p;
    v |= r1;
    *((unsigned int *) ((char *) r0 + 0x94)) = v;
}
