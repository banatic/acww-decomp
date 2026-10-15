/* func_020f70ec @ 0x020f70ec, 0x12c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020f70ec {
    unsigned char pad_00[8];
    unsigned char unk_08[5];
    unsigned char unk_0D;
    unsigned char unk_0E;
    unsigned char unk_0F;
} UnkStruct_020f70ec;

extern int func_020f7bc4(UnkStruct_020f70ec *self, int id, unsigned char *p);
extern void func_020f7218(UnkStruct_020f70ec *self);
extern void ciAddUNQUIETFilter(UnkStruct_020f70ec *self, void *arg);

void func_020f70ec(UnkStruct_020f70ec *self, int msg, void *arg)
{
    switch (msg) {
        case 10:
            switch (self->unk_0F) {
                case 0:
                    func_020f7bc4(self, 0x503, self->unk_08);
                    break;
                case 1:
                    func_020f7bc4(self, 0x505, self->unk_08);
                    break;
            }
            break;
        case 0x82:
            if (self->unk_0F == 0) {
                func_020f7bc4(self, 0x504, self->unk_08);
            }
            break;
        case 0x96:
            if (self->unk_0F == 1) {
                func_020f7bc4(self, 0x506, self->unk_08);
            }
            break;
        case 0x18f:
            self->unk_0D++;
            if (self->unk_0D == 7) {
                self->unk_0D = 0;
                func_020f7218(self);
            }
            self->unk_0F++;
            if (self->unk_0F == 3) {
                self->unk_0F = 0;
            }
            break;
    }
    ciAddUNQUIETFilter(self, arg);
}
