/* func_ov094_02299b74 @ 0x02299b74, 0xcc bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov094_02299c5c(void);
extern void func_ov094_02299c74(void *self, int);
extern void func_02004644(int, int);
extern void func_0200467c(int);
extern void func_ov094_022999a8(void *self, int);
extern int func_ov094_022999b0(void *self, int);
extern void func_ov094_022999a0(void *self, int);

typedef struct {
    int unk_00;
    int unk_04;
    unsigned char pad_08[0x0b];
    unsigned char unk_13;
    unsigned char pad_14[0x43a];
    unsigned short unk_44E[0x21];
} UnkStruct_02299b74;

void func_ov094_02299b74(UnkStruct_02299b74 *self)
{
    int ret = func_ov094_02299c5c();
    if (self->unk_13 != 0) {
        self->unk_13--;
        if (self->unk_13 == 0) {
            self->unk_00 = ret;
            func_ov094_02299c74(self, 0);
            func_02004644(0x2d, 1);
            func_0200467c(0x3e);
        } else {
            if (self->unk_00 >= ret) {
                goto subtract;
            }
            self->unk_00 = self->unk_00 + self->unk_04;
            goto done;
        subtract:
            self->unk_00 = self->unk_00 - self->unk_04;
        done:;
        }
        func_ov094_022999a8(self, 2);
    }
    if (func_ov094_022999b0(self, 2) != 0) {
        int value = self->unk_00;
        unsigned short *p;
        int i;
        func_ov094_022999a8(self, 1);
        p = &self->unk_44E[0];
        for (i = 0; i < 5; i++) {
            int rem = value % 10;
            int v = rem * 2;
            p[0] = (p[0] & 0xfc00) | (v + 0x2d8);
            p[0x20] = (p[0x20] & 0xfc00) | (v + 0x2d9);
            p--;
            value = value / 10;
        }
        func_ov094_022999a0(self, 2);
    }
}
