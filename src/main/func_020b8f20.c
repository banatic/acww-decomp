/* func_020b8f20 @ 0x020b8f20, 0xbe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208a844(void *self);
extern int func_020b8edc(void);
extern void func_020b8fe0(void *self);
extern void func_0200467c(int cmd);

typedef struct {
    unsigned char pad_00[0xe0];
    int unk_E0;
    unsigned char unk_E4;
    unsigned char unk_E5;
    unsigned char unk_E6;
    unsigned char unk_E7;
    unsigned char unk_E8;
} UnkStruct_020b8f20;

void func_020b8f20(UnkStruct_020b8f20 *self)
{
    int res;

    if (self->unk_E5 != 0) {
        res = func_0208a844(self);
        if (res == 0) {
            self->unk_E4 = 0;
            self->unk_E5 = 0;
            self->unk_E0 = 0;
            return;
        } else if (res == 2) {
            if (self->unk_E0 == 0) {
                func_0200467c(0x3d);
            }
            if (func_020b8edc() != 0) {
                self->unk_E0 = 0x19;
                return;
            }
            if (self->unk_E8 != 0) {
                self->unk_E0 = self->unk_E0 + 1;
                if (self->unk_E0 < 0x1e) {
                    return;
                }
                self->unk_E0 = 0;
                return;
            } else {
                self->unk_E0 = 1;
                return;
            }
        } else {
            return;
        }
    } else {
        if (self->unk_E4 != 0) {
            self->unk_E4 = 0;
            self->unk_E5 = 1;
            if (func_020b8edc() != 0) {
                self->unk_E0 = 0x19;
            } else {
                self->unk_E0 = 0;
            }
            func_020b8fe0(self);
        }
        return;
    }
}
