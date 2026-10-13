/* func_02077d04 @ 0x02077d04, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02077c40(void *);

void func_02077d04(void *param)
{
    int i;
    for (i = 0; i < 0x20; i++) {
        func_02077c40((char *) param + i * 0x24);
    }
}
