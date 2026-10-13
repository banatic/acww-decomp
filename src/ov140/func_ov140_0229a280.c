/* func_ov140_0229a280 @ 0x0229a280, 0x104 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x8af];
    u8 b[6];
    u8 tbl[0x20];
    u8 unk_8D5[6];
    char pad_8DB[2];
    u8 unk_8DD;
    char pad_8DE[2];
    u8 c[6];
    char pad_8E6[2];
    char unk_8E8;
} UnkStruct_0229a280;

extern void func_ov140_0229a41c(UnkStruct_0229a280 *self);
extern void func_02051bf8(u16 *buf, int n);
extern void func_02051c08(void *p, u16 *buf, int n);
extern void *func_ov140_0229a15c(UnkStruct_0229a280 *self);
extern int func_ov140_0229a1a4(UnkStruct_0229a280 *self, void *ent);
extern void func_ov139_02299798(void *p, int i);
extern void func_ov139_022997c0(void *p, int i, u16 *buf);

void func_ov140_0229a280(UnkStruct_0229a280 *self)
{
    u16 buf1[6];
    u16 buf2[10];
    void *h;
    int v;
    void *ent;
    int i;
    int j;
    int k;

    func_ov140_0229a41c(self);
    func_02051bf8(buf1, 6);
    func_02051bf8(buf2, 6);
    j = self->unk_8DD * 6;
    h = func_ov140_0229a15c(self);
    for (i = 0; i < 6; i++) {
        if (j < 0x20) {
            v = self->tbl[j];
            if (v == 0xff || (k = v, k = 0x23 * k, ent = (char *) h + 0x180 + k, func_ov140_0229a1a4(self, ent)) == 0) {
                self->b[i] = 0;
                self->c[i] = 0;
                func_ov139_02299798(&self->unk_8E8, i);
            } else {
                self->unk_8D5[i] = v;
                self->b[i] = 1;
                self->c[i] = *(u8 *) ((char *) h + k + 0x1a2);
                func_02051c08((char *) h + 0x190 + k, buf1, 6);
                func_02051c08(ent, buf2, 6);
                func_ov139_022997c0(&self->unk_8E8, i, buf1);
            }
        } else {
            self->b[i] = 0;
            self->c[i] = 0;
            func_ov139_02299798(&self->unk_8E8, i);
        }
        j++;
    }
}
