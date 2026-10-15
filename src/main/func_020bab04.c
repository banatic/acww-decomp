/* func_020bab04 @ 0x020bab04, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020bb090(void);
extern int func_0206fea4(void);
extern void func_020bae60(void);
extern void func_020bb3a4(int **p);
extern int func_020bbb20(int *p);
extern int func_0206fd34(void);
extern int func_0203adb0(void);
extern int func_020bb1b0(int **p);

extern int *data_021f75b0;
extern int data_021c67a4;

typedef struct {
    char pad_00[0x1c];
    int unk_1C;
    char pad_20[0x1e];
    short unk_3E;
} UnkStruct_020bab04;

extern UnkStruct_020bab04 data_021f8ab0;
extern int data_021f8ac4[];

void func_020bab04(void)
{
    func_020bb090();
    if (func_0206fea4() == 0) {
        func_020bae60();
        func_020bb3a4(&data_021f75b0);
    }
    func_020bbb20(data_021f75b0);
    if (data_021c67a4 != 0) {
        int a = (func_0206fd34() * 0x123) >> 12;
        int b = (func_0203adb0() * 0x1e) >> 12;
        int sum = a + b;
        data_021f8ac4[data_021f8ab0.unk_1C ^ 1] = sum;
    }
    data_021f8ab0.unk_3E = func_020bb1b0(&data_021f75b0);
}
