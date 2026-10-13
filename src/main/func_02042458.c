/* func_02042458 @ 0x02042458, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e9948(void *param0, int param1);
extern void func_02042484(void);

struct Func02042458_Data {
    unsigned char pad_00[0x20];
    int unk_20;
};

extern void *data_021fbe94;
extern struct Func02042458_Data data_021c779c;

void func_02042458(void)
{
    int result;

    result = func_020e9948(data_021fbe94, 0x10ec);
    data_021c779c.unk_20 = result;
    if (result != 0) {
        func_02042484();
    }
}
