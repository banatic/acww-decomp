/* func_020c2324 @ 0x020c2324, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, not used
// placeholder, not used

int func_020c2324(void *arg0)
{
    unsigned int *ptr;
    unsigned int val;

    ptr = (unsigned int *) ((char *) arg0 + 0x4e8);
    val = *ptr;
    *ptr = val & ~2u;
    *(unsigned short *) ((char *) arg0 + 0x714) = 0x28;
    return 1;
}
