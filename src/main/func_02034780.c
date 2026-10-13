/* func_02034780 @ 0x02034780, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02034780(void *arg0);

int func_02034780(void *arg0)
{
    if (*(unsigned int *) ((char *) arg0 + 0x28) == 3) {
        return 0;
    }
    return 1;
}
