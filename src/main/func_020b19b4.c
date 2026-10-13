/* func_020b19b4 @ 0x020b19b4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020b19b4(void *arg0)
{
    unsigned short *ptr;
    unsigned short value;

    value = 0;
    ptr = (unsigned short *) ((char *) arg0 + 0x4a0);
    *ptr = value;
    ptr = (unsigned short *) ((char *) arg0 + 0x4a2);
    *ptr = value;
}
