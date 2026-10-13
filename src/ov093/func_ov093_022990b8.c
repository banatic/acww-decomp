/* func_ov093_022990b8 @ 0x022990b8, 0x30 bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov093_022993c0(void *param1, int param2, int param3);

void func_ov093_022990b8(void *param0, int param1)
{
    int temp;
    int val;

    val = *(int *) ((char *) param0 + 8) + *(int *) ((char *) param0 + 0x10);
    *(int *) ((char *) param0 + 8) = val;
    temp = *(int *) ((char *) param0 + 8) >> 12;

    func_ov093_022993c0(param0, 4, temp - 0xc0);

    if (param1 != 0) {
        func_ov093_022993c0(param0, 0, temp);
    }
}
