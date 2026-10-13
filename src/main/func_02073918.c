/* func_02073918 @ 0x02073918, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073918(void *r0, int r1);

int func_02073918(void *r0, int r1)
{
    if (r1 == *(int *) ((char *) r0 + 0x64)) {
        return 1;
    }
    return 0;
}
