/* func_020b88f0 @ 0x020b88f0, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d2270[];

extern void *func_020a8228(void *);
extern void *func_020a8210(void *);
extern int func_020b4980(unsigned char *, unsigned char *, int);
extern void func_0208aa48(void *, unsigned char *);
extern void func_0208a9e4(void *, int);
extern void func_020b8fe0(void *);

typedef struct UnkStruct_020b88f0 {
    unsigned char pad_00[8];
    unsigned char sub[0xf4];
    int unk_FC;
    unsigned char pad_100[4];
    int unk_104;
    unsigned char pad_108[4];
    unsigned char unk_10C;
} UnkStruct_020b88f0;

typedef struct Locals {
    unsigned char byte_var;
    unsigned char pad_01[3];
    unsigned char buf[0x60];
} Locals;

void func_020b88f0(UnkStruct_020b88f0 *self, int flag)
{
    Locals local;
    int r2, r3, r4, cond;
    unsigned char old_byte;

    func_020a8228(local.buf);

    local.byte_var = data_020d2270[self->unk_FC];
    r2 = (self->unk_FC == 1) ? 1 : 0;
    r3 = (self->unk_FC == 2) ? 1 : 0;
    r4 = 1;
    if (r2 == 0 && r3 == 0) {
        r4 = 0;
    }

    old_byte = self->unk_10C;
    self->unk_10C = 0;

    if (flag != 0) {
        self->unk_104 = 0;
        cond = 1;
    } else {
        cond = old_byte;
        if (r4 != 0) {
            cond = 1;
        }
    }

    if (cond != 0) {
        if (self->unk_104 == 1) {
            if (r2 != 0) {
                local.byte_var = 0x93;
            } else if (r3 != 0) {
                local.byte_var = 0x94;
            }
        }
        func_020b4980(local.buf, &local.byte_var, 0);
        func_0208aa48(&self->sub, local.buf);
        if (flag == 0) {
            func_0208a9e4(&self->sub, 1);
            func_020b8fe0(&self->sub);
        }
    }

    if (r4 != 0) {
        self->unk_104++;
        if (self->unk_104 >= 2) {
            self->unk_104 = 0;
        }
    }

    func_020a8210(local.buf);
}
