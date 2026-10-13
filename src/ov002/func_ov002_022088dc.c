/* func_ov002_022088dc @ 0x022088dc, 0x12 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

int func_ov002_022088dc(void *p)
{
    return (*(unsigned char *) ((char *) p + 0x10) & 0x10) ? 1 : 0;
}
