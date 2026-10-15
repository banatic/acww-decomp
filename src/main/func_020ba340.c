/* func_020ba340 @ 0x020ba340, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021f8ab0;
extern int data_021f8b48;
typedef struct UnkStruct_020be2d4_2 UnkStruct_020be2d4_2;

extern void func_020be2d4(UnkStruct_020be2d4_2 *self, void *arg);

void func_020ba340(void)
{
    *(int *) ((char *) ((int) &data_021f8ab0) + (28)) = (*(int *) ((char *) ((int) &data_021f8ab0) + (28)) ^ 1);
    func_020be2d4((UnkStruct_020be2d4_2 *) &data_021f8b48, &data_021f8ab0);
}
