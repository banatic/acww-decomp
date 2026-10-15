/* func_ov048_02261ddc @ 0x02261ddc, 0x40 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02261ddc UnkStruct_02261ddc;

extern void func_ov048_02261d08(UnkStruct_02261ddc *self);
extern unsigned char func_ov048_022609fc(void *receiver);
extern void func_0206844c(void *a, char *b, void *d);
extern void *data_ov048_02263d20;

struct UnkStruct_02261ddc {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0x7CF];
    unsigned char unk_813;
};

void func_ov048_02261ddc(UnkStruct_02261ddc *self, int ev)
{
    if (ev == 1) {
        self->unk_813 = 1;
        func_ov048_02261d08(self);
    } else if (ev == 2) {
        char local;
        local = func_ov048_022609fc(self);
        func_0206844c(self->unk_40, &local, data_ov048_02263d20);
    }
}
