/* func_0200570c @ 0x0200570c, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

// placeholder, not used directly

void func_0200570c(unsigned int *arg0)
{
    unsigned int *puVar1;
    unsigned int val;
    unsigned int *puVar3;

    puVar1 = (unsigned int *) (arg0 + 0x17);
    val = *puVar1;
    *(unsigned int *) ((unsigned char *) arg0 + 0x6f4) = val;
    val = *(puVar1 + 1);
    *(unsigned int *) ((unsigned char *) arg0 + 0x6f8) = val;
    val = *(puVar1 + 2);
    *(unsigned int *) ((unsigned char *) arg0 + 0x6fc) = val;
    return;
}
