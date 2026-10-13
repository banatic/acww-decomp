/* func_ov003_02218dfc @ 0x02218dfc, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0xfc];
    char unk_8F0;
    char pad_8F1[0x393];
    unsigned short unk_C84;
} UnkStruct_02218dfc;

extern void func_ov003_02218eac(char *p, Pair *p2);
extern void func_ov003_02218ec4(void *p, Pair *p2, int count, int val);

void func_ov003_02218dfc(UnkStruct_02218dfc *self, int arg2)
{
    Pair local1, local2;

    if (self->unk_7F0 == 0x16) {
        self->unk_C84 = (unsigned short) arg2;
        return;
    }
    local1.a = 0;
    local1.b = 0;
    func_ov003_02218eac(&self->unk_8F0, &local1);
    local2.a = local1.a;
    local2.b = local1.b;
    func_ov003_02218ec4(self, &local2, 6, arg2);
}
