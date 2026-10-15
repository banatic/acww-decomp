/* func_ov047_02260e18 @ 0x02260e18, 0x2c bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02015094(void *);
extern void func_ov047_02261618(void *);

typedef struct {
    unsigned char pad_00[0xcc];
    unsigned char unk_CC;
    unsigned char pad_CD[3];
    int unk_D0;
} UnkStruct_02260e18;

void func_ov047_02260e18(UnkStruct_02260e18 *self)
{
    func_02015094(self);
    func_ov047_02261618(self);

    if (self->unk_CC == 0) {
        self->unk_D0 = 0x27;
    } else {
        self->unk_D0 = 0x20;
    }
}
