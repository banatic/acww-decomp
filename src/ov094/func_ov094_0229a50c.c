/* func_ov094_0229a50c @ 0x0229a50c, 0x18 bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov094_0229bc64[];

int func_ov094_0229a50c(unsigned int index)
{
    if (index >= 10) {
        return 0x1000;
    }
    return data_ov094_0229bc64[index];
}
