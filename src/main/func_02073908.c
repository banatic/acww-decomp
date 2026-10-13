/* func_02073908 @ 0x02073908, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073908(void *arg0, int arg1);

int func_02073908(void *arg0, int arg1)
{
    if (arg1 == *(int *) ((char *) arg0 + 0x68)) {
        return 1;
    }
    return 0;
}
