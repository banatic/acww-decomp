/* func_02099df4 @ 0x02099df4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02064294(void *);
extern int func_02003704(void *);

int func_02099df4(void *arg)
{
    if (func_02064294(arg) && func_02003704((char *) arg + 0xe)) {
        return 1;
    }
    return 0;
}
