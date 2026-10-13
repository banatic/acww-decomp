/* func_02010680 @ 0x02010680, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011368(void *a, int b);
extern int func_0205d3d4(void *a, int b, int c, int d, int e);

int func_02010680(void *a, int b)
{
    return func_0205d3d4((char *) a + 0x774, b, func_02011368(a, b), 0, 0);
}
