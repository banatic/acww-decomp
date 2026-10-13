/* func_ov122_0229fcfc @ 0x0229fcfc, 0x38 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x9C];
    int unk_9C;
    int unk_A0;
    char pad_A4[6];
    char unk_AA;
} UnkStruct_0229fcfc;

extern void func_ov122_0229efd8(UnkStruct_0229fcfc *self, int a, int b);
extern int func_ov122_0229fc9c(UnkStruct_0229fcfc *self, int *p);
extern void func_ov122_0229f590(UnkStruct_0229fcfc *self, int a);

void func_ov122_0229fcfc(UnkStruct_0229fcfc *self)
{
    int ret;

    self->unk_AA = 3;
    func_ov122_0229efd8(self, 0x1000, 3);
    self->unk_A0 = 0x88;
    ret = func_ov122_0229fc9c(self, &self->unk_9C);
    func_ov122_0229f590(self, ret);
}
