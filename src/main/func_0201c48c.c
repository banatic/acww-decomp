/* func_0201c48c @ 0x0201c48c, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201c6a8(void);

void func_0201c48c(void *param)
{
    unsigned char *ptr;

    *(unsigned int *) ((char *) param + 0x24) = (unsigned int) func_0201c6a8;
    ptr = (unsigned char *) param + 0x92;
    *ptr = 1;
}
