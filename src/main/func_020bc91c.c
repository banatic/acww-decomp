/* func_020bc91c @ 0x020bc91c, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020bc91c {
    char pad_00[0x2f30];
    int unk_2F30;
};

extern void func_020bca80(struct UnkStruct_020bc91c *obj, int a, int b, int c);
extern void func_020bc9c4(struct UnkStruct_020bc91c *obj, int d);
extern void func_020bcd30(struct UnkStruct_020bc91c *obj);

void func_020bc91c(struct UnkStruct_020bc91c *obj)
{
    int val = obj->unk_2F30;
    if (val < 0) {
        func_020bca80(obj, 200, 100, 600);
    } else if (val == 0) {
        func_020bc9c4(obj, 20);
    }
    func_020bcd30(obj);
}
