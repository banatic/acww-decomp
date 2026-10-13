/* func_ov003_0222f67c @ 0x0222f67c, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0222f67c;
extern UnkStruct_0222f67c *data_020ccf94;
extern void func_ov003_0222efc0(void *a);
extern int func_02073dd4(void *a, int b);
extern void func_ov003_0222ed90(void *a);
extern void func_ov003_0222ec74(void *a);
extern void func_ov003_0222f320(void *a);

int func_ov003_0222f67c(void *self)
{
    func_ov003_0222efc0(self);
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0) {
        func_ov003_0222ed90(self);
    }
    func_ov003_0222ec74(self);
    func_ov003_0222f320(self);
    return 1;
}
