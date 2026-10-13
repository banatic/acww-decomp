/* func_02003658 @ 0x02003658, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020c7570[];

int func_02003658(unsigned int arg)
{
    int result = 5;

    if (arg < 6) {
        result = data_020c7570[arg];
    }

    return result;
}
