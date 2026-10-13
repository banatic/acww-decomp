/* func_020bc98c @ 0x020bc98c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2f30];
    int unk_2F30;
} UnkStruct_020bc98c;

extern void func_020bca80(UnkStruct_020bc98c *, int, int, int);
extern void func_020bc9c4(UnkStruct_020bc98c *, int);
extern void func_020bcd30(UnkStruct_020bc98c *);

void func_020bc98c(UnkStruct_020bc98c *param)
{
    int value = param->unk_2F30;
    if (value < 0) {
        func_020bca80(param, 20, 100, 400);
    } else if (value == 0) {
        func_020bc9c4(param, 20);
    }
    func_020bcd30(param);
}
