/* func_020ba340 @ 0x020ba340, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f8ab0;
extern int data_021f8b48;
extern void func_020be2d4(int, int);

void func_020ba340(void)
{
    *(int *) ((char *) ((int) &data_021f8ab0) + (28)) = (*(int *) ((char *) ((int) &data_021f8ab0) + (28)) ^ 1);
    func_020be2d4((int) &data_021f8b48, (int) &data_021f8ab0);
}
