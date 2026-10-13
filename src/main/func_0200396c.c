/* func_0200396c @ 0x0200396c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020d5c64;
extern void func_0208a1f0(char *ptr, void *arg2);
extern void func_0208a1ec(char *ptr, int val);
extern void func_0208a1e0(char *ptr, int val1, int val2);
extern void func_0208a158(char *ptr);
extern void func_0208a144(char *ptr);

struct UnkStruct_0200396c {
    char pad_00[0xc];
    char unk_0C;
    char pad_0D[0x33 - 0xc - 1];
    char unk_33;
};

void func_0200396c(struct UnkStruct_0200396c *obj, int flag)
{
    func_0208a1f0(&obj->unk_0C, &data_020d5c64);
    if (flag != 0) {
        func_0208a1ec(&obj->unk_0C, 1);
        func_0208a1e0(&obj->unk_0C, 1, 0);
        func_0208a158(&obj->unk_0C);
    } else {
        func_0208a1ec(&obj->unk_0C, 0);
        func_0208a144(&obj->unk_0C);
    }
    obj->unk_33 = 0;
}
