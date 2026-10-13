/* func_ov003_02236230 @ 0x02236230, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *data_ov003_02262b38[];

int func_ov003_02236230(void *o)
{
    int i = ((int *) o)[2] & 7;
    if (data_ov003_02262b38[i] == o) {
        data_ov003_02262b38[i] = 0;
        return 1;
    }
    return 0;
}
