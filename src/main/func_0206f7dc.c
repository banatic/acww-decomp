/* func_0206f7dc @ 0x0206f7dc, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fbf8(int);

extern unsigned char data_021cfc80[];
extern unsigned char data_021cfc88[];

int func_0206f7dc(int param1, int param2)
{
    int result;
    int *ptr1;
    int *ptr2;

    if (func_0206fbf8(0x3d) != 0) {
        ptr1 = (int *) data_021cfc80;
        *ptr1 = param1;
        ptr2 = (int *) data_021cfc88;
        *ptr2 = param2;
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
