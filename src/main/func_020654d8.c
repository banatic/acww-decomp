/* func_020654d8 @ 0x020654d8, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02065558(void *param1, void *param2, void *param3);

void func_020654d8(void *param1, void *param2, void *param3)
{
    int i;
    int *p;

    i = 0;
    do {
        p = (int *) param1;
        if (*p == 2) {
            func_02065558(param1, param2, param3);
        }
        i++;
    } while (i < 4);
}
