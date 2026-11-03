/* owl_3: 4 functions, module ov047
 * mwccarm 1.2/base -O4,s
 * func_ov047_022620f4 @ 0x022620f4, 0x38 bytes, Thumb
 * func_ov047_0226209c @ 0x0226209c, 0x58 bytes, Thumb
 * func_ov047_02262098 @ 0x02262098, 0x4 bytes, Thumb
 * func_ov047_02262094 @ 0x02262094, 0x4 bytes, Thumb
 */

struct UnkStruct_0226209c {
    char pad_00[0x64];
    int unk_64;
};

extern void func_0201ad18(int, int, int, int, int, int, int, int);
extern unsigned char data_020c814c[];
extern unsigned char data_021fbee8[];
extern int func_0201c0e0(int);
extern int func_0201c040(int, int *, int *);
extern int func_020a7278(void);
extern void func_0201c054(int, int, int, int);
extern void func_ov047_022624f4(int, int);
extern struct UnkStruct_0226209c *data_020ccf94;

int func_ov047_022620f4(int a)
{
    func_0201ad18(a + 0x3b0, 0, 0, 0, (unsigned int) data_021fbee8, 4, *((int *) data_020c814c), 1);
    return 1;
}

int func_ov047_0226209c(int arg)
{
    int a, b;
    if (func_0201c0e0(arg) != 0) {
        a = 4;
        b = 4;
        if (func_0201c040(arg, &a, &b) != 0) {
            if (a == 4) {
                if (func_020a7278() != 0) {
                    func_0201c054(arg, 1, data_020ccf94->unk_64, 4);
                    func_ov047_022624f4(arg, 0);
                }
            }
        }
    }
    return 1;
}

int func_ov047_02262098(void)
{
    return 1;
}

int func_ov047_02262094(void)
{
    return 1;
}
