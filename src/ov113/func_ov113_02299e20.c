/* func_ov113_02299e20 @ 0x02299e20, 0x78 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

extern int data_021eed68;
extern int func_020781d0(void *, int arg1);
extern int func_020984d4(void);
extern int func_02078268(int, int);
extern void func_0206fdd4(void *, int, int, int, int, int);
extern int func_02078234(int);
extern void func_02078248(int, int);
extern void func_ov113_02299d94(void *, int);

typedef struct UnkStruct_02299e20 {
    char pad_00[0xa0];
} UnkStruct_02299e20;

void func_ov113_02299e20(UnkStruct_02299e20 *p, int cond1)
{
    int ret1;
    int ret2;

    int cond2;
    int arg6;
    int arg6_2;

    ret1 = func_020781d0(&data_021eed68, cond1);
    ret2 = func_020984d4();

    cond1 = func_02078268(ret1, ret2);
    if (cond1 != 0) {
        arg6 = 8;
    } else {
        arg6 = 10;
    }
    func_0206fdd4((char *) p + 0xa0, 0x10, 0, 0x12, 3, arg6);

    cond2 = func_02078234(ret1);
    if (cond2 != 0) {
        arg6_2 = 10;
    } else {
        arg6_2 = 8;
    }
    func_0206fdd4((char *) p + 0xa0, 6, 5, 0x19, 6, arg6_2);

    func_ov113_02299d94(p, 1);
    func_02078248(ret1, ret2);
}
