/* group_params_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0206f7dc @ 0x0206f7dc, 0x30 bytes, Thumb
 * func_0206f7c8 @ 0x0206f7c8, 0x14 bytes, Thumb
 * func_0206f7bc @ 0x0206f7bc, 0xc bytes, Thumb
 * func_0206f7b0 @ 0x0206f7b0, 0xc bytes, Thumb
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

void func_0206f7c8(void)
{
    (*(int *) data_021cfc80) = 0;
    (*(int *) data_021cfc88) = 0;
}

unsigned int *func_0206f7bc(void)
{
    return *(unsigned int **) data_021cfc80;
}

int func_0206f7b0(void)
{
    return (*(int *) data_021cfc88);
}
