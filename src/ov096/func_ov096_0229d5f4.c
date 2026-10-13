/* func_ov096_0229d5f4 @ 0x0229d5f4, 0x70 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d5f4 UnkStruct_0229d5f4;

extern void func_ov096_0229e95c(UnkStruct_0229d5f4 *, int);
extern int func_ov096_0229f290(UnkStruct_0229d5f4 *, int);
extern int func_ov096_0229f200(UnkStruct_0229d5f4 *, int);
extern int func_0206fe54(void);
extern void func_ov002_02208098(UnkStruct_0229d5f4 *, int);
extern void func_ov094_0229b1d8(void *);

struct UnkStruct_0229d5f4 {
    char pad_00[0xa4];
    int unk_A4;
    int unk_A8;
    char pad_AC[0xb6 - 0xac];
    unsigned char unk_B6;
    char pad_B7[0xdb8 - 0xb7];
    char unk_DB8;
};

void func_ov096_0229d5f4(UnkStruct_0229d5f4 *self)
{
    unsigned char b = self->unk_B6;
    func_ov096_0229e95c(self, b);
    self->unk_A4 = func_ov096_0229f290(self, b);
    self->unk_A8 = func_ov096_0229f200(self, b);
    if (func_0206fe54()) {
        self->unk_A4 -= 2;
        self->unk_A8 -= 2;
    }
    func_ov002_02208098(self, 0x2a);
    func_ov094_0229b1d8(&self->unk_DB8);
}
