/* func_ov009_022655ac @ 0x022655ac, 0x16 bytes, Thumb, module ov009
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02107828(void *p0);

void *func_ov009_022655ac(void *a0)
{
    char *p = (char *) func_02107828(a0);
    return p + *(int *) (p + *(unsigned short *) (p + 0xe) + 0xc);
}
