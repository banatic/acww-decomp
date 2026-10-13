/* func_02073820 @ 0x02073820, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *);

void func_02073820(void *param)
{
    if (func_02073d90(param)) {
        *(unsigned int *) ((char *) param + 0xd0) = *(unsigned int *) ((char *) param + 0xcc);
        *(unsigned int *) ((char *) param + 0xd4) = *(unsigned int *) ((char *) param + 0xcc) + 5;
    }
}
