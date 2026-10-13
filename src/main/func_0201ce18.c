/* func_0201ce18 @ 0x0201ce18, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0201ce18(void *arg0);

unsigned int func_0201ce18(void *arg0)
{
    unsigned int val;
    unsigned int *puVar2;

    puVar2 = (unsigned int *) ((unsigned int) arg0 + 0x644);
    val = *puVar2;
    if (val != 0) {
        return 1;
    }
    return 0;
}
