/* func_ov003_02236254 @ 0x02236254, 0x20 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_02262b38[8];

int func_ov003_02236254(void *s)
{
    int i = *(int *) ((char *) s + 8) & 7;
    if (data_ov003_02262b38[i] != 0) {
        return 0;
    }
    data_ov003_02262b38[i] = s;
    return 1;
}
