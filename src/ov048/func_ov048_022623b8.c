/* func_ov048_022623b8 @ 0x022623b8, 0x38 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov048_022635f4(int, int);
extern void func_0207428c(int);
extern int func_020ec1e8(void);
extern void func_ov048_022616b8(void *, int);
extern void func_ov048_02262658(void *);

typedef struct {
    char pad_00[0xb8];
    int unk_B8;
} UnkStruct_022623b8;

void func_ov048_022623b8(UnkStruct_022623b8 *self)
{
    func_0207428c(func_ov048_022635f4(self->unk_B8, 7));
    if (func_020ec1e8() == 3 || func_020ec1e8() == 4) {
        func_ov048_022616b8(self, 20);
    } else {
        func_ov048_02262658(self);
    }
}
