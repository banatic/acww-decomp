/* func_020abb78 @ 0x020abb78, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020aca30(int *ptr);

int func_020abb78(int *obj)
{
    obj[0x4f] = 3;
    return func_020aca30(&obj[0x39]);
}
