/* sky: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020ba35c @ 0x020ba35c, 0x10 bytes, Thumb
 * func_020ba340 @ 0x020ba340, 0x1c bytes, Thumb
 */

typedef struct UnkStruct_020be2d4_2 UnkStruct_020be2d4_2;

extern int data_021f8b48;
extern void func_020bdf68(int *a, int b);
extern int data_021f8ab0;
extern void func_020be2d4(UnkStruct_020be2d4_2 *self, void *arg);

void func_020ba35c(int b)
{
    func_020bdf68(&data_021f8b48, b);
}

void func_020ba340(void)
{
    *(int *) ((char *) ((int) &data_021f8ab0) + (28)) = (*(int *) ((char *) ((int) &data_021f8ab0) + (28)) ^ 1);
    func_020be2d4((UnkStruct_020be2d4_2 *) &data_021f8b48, &data_021f8ab0);
}
