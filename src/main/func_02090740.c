/* func_02090740 @ 0x02090740, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02090424(void *);

void func_02090740(char *param)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_02090424(param + 4 + i * 0x148);
    }
}
