/* func_0209d938 @ 0x0209d938, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209d95c(void *param, int idx);

int func_0209d938(void *param)
{
    int count = 0;
    unsigned int i = count;
    do {
        if (func_0209d95c(param, i)) {
            count++;
        }
        i++;
    } while (i < 4);
    return count;
}
