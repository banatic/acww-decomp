/* func_02002e14 @ 0x02002e14, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void G3X_SetClearColor(int, int, int, int, int);

extern unsigned char data_0213feac[];
extern unsigned char data_0213feb0[];

void func_02002e14(void)
{
    int stack_var;
    unsigned short *ptr_0x0213feac;
    int *ptr_0x0213feb0;

    stack_var = 1;
    ptr_0x0213feac = (unsigned short *) data_0213feac;
    ptr_0x0213feb0 = (int *) data_0213feb0;
    G3X_SetClearColor(*ptr_0x0213feac, 0, *ptr_0x0213feb0, 0x3f, stack_var);
}
