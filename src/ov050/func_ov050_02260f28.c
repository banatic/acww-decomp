/* func_ov050_02260f28 @ 0x02260f28, 0x118 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02260f28 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    unsigned int unk_40;
    char pad_44[0xb4 - 0x44];
    void *unk_B4;
    char pad_B8[0xd0 - 0xb8];
    int unk_D0;
} UnkStruct_02260f28;

extern int func_020160b4(UnkStruct_02260f28 *self);
extern int func_020ab504(void *argument0);
extern int func_020984e8(void);
extern void func_ov050_02263640(UnkStruct_02260f28 *self, int arg);
extern int func_0202e9fc(void);
extern int func_020ada14(void);
extern int func_0209ded0(void);
extern int func_020874c4(void *ptr);
extern void func_02015fb0(UnkStruct_02260f28 *self, int a, int b, int c, int d, int e);
extern int func_ov050_02260510(void *p);
extern int func_0202ea40(void *p, char *buffer, int count);
extern void func_0202ea28(void *p, char *buffer);
extern void func_0206844c(unsigned int val, char *str, void *data);

extern int data_021f3b0c;
extern unsigned char data_ov050_02265824[];

void func_ov050_02260f28(UnkStruct_02260f28 *self)
{
    int r5;
    char buffer[2];
    int *gp;

    r5 = func_020ab504((void *) func_020160b4(self));
    func_020984e8();
    gp = &data_021f3b0c;

    if ((int) self->unk_1E > 0x14) {
        return;
    }

    self->unk_D0 = 0xff;

    if (r5 != 3) {
        func_ov050_02263640(self, 5);
    }

    switch (r5) {
        case 0:
            self->unk_D0 = 7;
            break;
        case 1:
            if (func_0202e9fc() == 0) {
                self->unk_D0 = 0x59;
            } else if (func_020ada14() != 0) {
                self->unk_D0 = 0x18;
            } else {
                self->unk_D0 = 0x17;
            }
            break;
        case 2:
            if (func_0209ded0()) {
                int ret = func_020874c4(gp);
                func_02015fb0(self, ret, 1, 3, 0, 0);
                self->unk_D0 = 0x16;
            } else {
                self->unk_D0 = 0x0d;
            }
            break;
        case 3:
            if (func_ov050_02260510(self->unk_B4)) {
                if (func_0202ea40(self->unk_B4, buffer, 3)) {
                    func_0202ea28(self->unk_B4, buffer);
                }
            }
            break;
        case 4:
            self->unk_D0 = 0x15;
            break;
    }

    if (self->unk_D0 != 0xff) {
        buffer[1] = (char) self->unk_D0;
        func_0206844c(self->unk_40, &buffer[1], data_ov050_02265824);
    }
}
