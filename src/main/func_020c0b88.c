/* func_020c0b88 @ 0x020c0b88, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bec54(void *ptr, int value);
extern int data_021fba00[];

void func_020c0b88(void)
{
    int *ptr = data_021fba00;
    unsigned int i;
    for (i = 0; i < 5; i++) {
        func_020bec54(ptr, i + 10);
    }
}
