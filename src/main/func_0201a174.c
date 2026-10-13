/* func_0201a174 @ 0x0201a174, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201a1d4(void *param1, int param2, int param3);

void func_0201a174(void *param1)
{
    int temp;

    if (*(int *) ((char *) param1 + 0x7c) == 0x16f) {
        *(int *) ((char *) param1 + 0x7c) = 0xba;
    }

    temp = *(int *) ((char *) param1 + 0x7c);
    func_0201a1d4(param1, temp, 0);
    *(int *) ((char *) param1 + 0x7c) = 0x16f;
}
