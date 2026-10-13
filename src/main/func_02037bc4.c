/* func_02037bc4 @ 0x02037bc4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ca008[];

int func_02037bc4(int index)
{
    if (index < 0x37) {
        return data_020ca008[index];
    } else {
        return 0;
    }
}
