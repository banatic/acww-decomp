/* func_ov004_022254e4 @ 0x022254e4, 0x58 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022254e4 {
    char pad_00[0x64];
    int unk_64;
};
extern int func_0201c0e0(int);
extern int func_0201c040(int, int *, int *);
extern int func_020a7278(void);
extern void func_0201c054(int, int, int, int);
extern void func_ov004_022256ec(int, int);
extern struct UnkStruct_022254e4 *data_020ccf94;

int func_ov004_022254e4(int arg)
{
    int a, b;
    if (func_0201c0e0(arg) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040(arg, &a, &b) != 0) {
            if (a == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054(arg, 1, data_020ccf94->unk_64, 4);
                    func_ov004_022256ec(arg, 3);
                }
            }
        }
    }
    return 1;
}
