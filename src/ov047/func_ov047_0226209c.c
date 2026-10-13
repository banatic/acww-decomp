/* func_ov047_0226209c @ 0x0226209c, 0x58 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226209c {
    char pad_00[0x64];
    int unk_64;
};
extern int func_0201c0e0(int);
extern int func_0201c040(int, int *, int *);
extern int func_020a7278(int);
extern void func_0201c054(int, int, int, int);
extern void func_ov047_022624f4(int, int);
extern struct UnkStruct_0226209c *data_020ccf94;

int func_ov047_0226209c(int arg)
{
    int a, b;
    if (func_0201c0e0(arg) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040(arg, &a, &b) != 0) {
            if (a == 4) {
                if (func_020a7278(a) != 0) {
                    func_0201c054(arg, 1, data_020ccf94->unk_64, 4);
                    func_ov047_022624f4(arg, 0);
                }
            }
        }
    }
    return 1;
}
