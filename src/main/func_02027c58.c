/* func_02027c58 @ 0x02027c58, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, not used

void func_02027c58(void *r0)
{
    unsigned int *r1;
    r1 = *(unsigned int **) ((char *) r0 + 0x40);
    if (r1 != 0) {
        *((unsigned int *) r1 + 2) = 1;
    }
}
