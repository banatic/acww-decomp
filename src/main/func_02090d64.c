/* func_02090d64 @ 0x02090d64, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02090d70(void *);

int func_02090d64(void *self)
{
    return func_02090d70(*(void **) ((char *) self + 12));
}
