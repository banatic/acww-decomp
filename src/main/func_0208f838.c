/* func_0208f838 @ 0x0208f838, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208f7f8(void *param1);

void func_0208f838(void *param1)
{
    int temp;

    temp = *(int *) ((char *) param1 + 0x24);
    if (temp > 0) {
        temp--;
        *(int *) ((char *) param1 + 0x24) = temp;
        if (*(int *) ((char *) param1 + 0x24) > 0) {
            return;
        }
        func_0208f7f8(param1);
    }
}
