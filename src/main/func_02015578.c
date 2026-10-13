/* func_02015578 @ 0x02015578, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_02015578(char *p)
{
    unsigned int *r2;
    r2 = *(unsigned int **) (p + 0x40);
    if (r2 != 0) {
        *(unsigned int *) ((char *) r2 + 0x14) = *(unsigned int *) (p + 0xa8);
        *(p + 0xac) = 1;
    }
    return 0;
}
