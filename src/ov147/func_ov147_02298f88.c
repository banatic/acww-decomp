/* func_ov147_02298f88 @ 0x02298f88, 0x80 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int func_0200277c(int);
extern int func_0203de68(int);
extern void func_ov147_02298f54(void *self, void *p, int i);
extern void func_020b9c10(void *dst, void *src, int a, int b, int c, int d);

typedef struct {
    char pad_00[0xa4];
    int unk_A4;
    char pad_A8[0xd0 - 0xa8];
    char unk_D0;
} UnkStruct_02298f88;

typedef struct {
    char data[32];
} UnkStruct_02298f88_2;

extern UnkStruct_02298f88_2 data_ov147_0229ae0c[];
extern char data_ov147_0229f2ac[];

int func_ov147_02298f88(UnkStruct_02298f88 *self)
{
    if (self->unk_A4 == 0) {
        func_0200277c(5);
        func_0203de68(1);
        return 1;
    } else {
        int i;
        UnkStruct_02298f88_2 *p;

        self->unk_A4--;
        p = &data_ov147_0229ae0c[self->unk_A4];
        for (i = 0; i < 448; i++) {
            func_ov147_02298f54(self, p, i);
        }
        func_020b9c10(&self->unk_D0, data_ov147_0229f2ac, 5, 0x140, 0x140, 0x2ff);
        return 0;
    }
}
