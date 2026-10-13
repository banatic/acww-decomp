/* func_02054170 @ 0x02054170, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02054170(void *arg0)
{
    unsigned int *ptr;
    unsigned int val;

    ptr = (unsigned int *) ((char *) arg0 + 0x1b0);
    *ptr = 0;
    val = *ptr;
    *(unsigned int *) ((char *) arg0 + 0x1ac) = val;
}
