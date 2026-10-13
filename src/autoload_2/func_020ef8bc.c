/* func_020ef8bc @ 0x020ef8bc, 0x14 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ef8bc(void *p);

int func_020ef8bc(void *p)
{
    unsigned char b = *(unsigned char *) ((char *) p + 9);
    if (b & 4) {
        return 1;
    } else {
        return 0;
    }
}
