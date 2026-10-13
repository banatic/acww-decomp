/* func_02005730 @ 0x02005730, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020058b4(void);

void func_02005730(void *arg0)
{
    unsigned char *ptr;

    *(unsigned int *) ((char *) arg0 + 0x24) = (unsigned int) func_020058b4;
    ptr = (unsigned char *) arg0 + 0x92;
    *ptr = 1;
}
