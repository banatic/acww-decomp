/* func_02044858 @ 0x02044858, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_02073d90(int);

int func_02044858(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    result = func_02073d90(*(unsigned int *) &data_020ccf94);
    if (result == 0) {
        r4 = 0;
    }
    return r4;
}
