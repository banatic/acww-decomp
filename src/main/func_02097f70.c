/* func_02097f70 @ 0x02097f70, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02097f70(void *ptr, unsigned int mask)
{
    unsigned short val;
    val = *(unsigned short *) ((char *) ptr + 0x0a04);
    return (val & mask) ? 1 : 0;
}
