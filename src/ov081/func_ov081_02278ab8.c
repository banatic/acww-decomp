/* func_ov081_02278ab8 @ 0x02278ab8, 0xb0 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov081_02279868[];
extern unsigned char data_ov081_02279878[];

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char unk_1E;
    unsigned char pad_1F[0x21];
    void *unk_40;
    unsigned char pad_44[0x84];
    int unk_C8;
} UnkStruct_02278ab8;

int func_020160b4(void *self);
int func_020ab504(void *argument0);
void func_0209a050(int val);
int func_02015330(void *self, void *cmd, int a, int b, int c);
void func_0206844c(void *obj, unsigned char *cmd, unsigned char *data);
int func_ov081_02278da8(void *self);

void func_ov081_02278ab8(UnkStruct_02278ab8 *self)
{
    int t;
    int val;
    unsigned char cmd[4];
    unsigned char *p;
    int r4;

    t = func_020ab504((void *) func_020160b4(self));
    p = data_ov081_02279868;
    r4 = 0xff;
    val = self->unk_C8;

    if (val < 0) {
        goto L16;
    }

    p = data_ov081_02279878;
    if (self->unk_1E != 0) {
        goto L2;
    }
    if (t != 0) {
        goto L2;
    }
    if (val < 0) {
        goto L0;
    }

    func_0209a050(val);
    *(unsigned short *) (cmd + 2) = 0x37e0;
    func_02015330(self, cmd + 2, 0, 5, 0);

L0:
    r4 = 2;
L2:
    if (r4 != 0xff) {
        cmd[0] = (unsigned char) r4;
        func_0206844c(self->unk_40, cmd, p);
    }
    return;

L16:
    if (self->unk_1E == 8) {
        if (t != 0) {
            if (func_ov081_02278da8(self) == 0) {
                r4 = 9;
            } else if (func_ov081_02278da8(self) > 0) {
                r4 = 10;
            }
        } else {
            r4 = 11;
        }
    }
    if (r4 != 0xff) {
        cmd[1] = (unsigned char) r4;
        func_0206844c(self->unk_40, cmd + 1, p);
    }
}
