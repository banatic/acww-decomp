/* func_02097a54 @ 0x02097a54, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02097958(void *);
extern int func_02097a74(int, int, int);

int func_02097a54(int arg0)
{
    int val;
    int val2;

    val = func_02097958((void *) arg0);
    if (val < 0) {
        val2 = 0;
    } else {
        val2 = func_02097a74(arg0, val, 0);
    }
    return val2;
}
