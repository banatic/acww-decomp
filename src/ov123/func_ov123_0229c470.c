/* func_ov123_0229c470 @ 0x0229c470, 0xa8 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov123_0229bf04(void);
extern void func_ov123_0229be60(void *);
extern void func_ov123_0229a278(void *, int);
extern void func_ov123_0229bdfc(void *receiver);
extern int func_0206fca4(void);
extern void func_ov123_0229b508(void *);
extern void func_ov123_0229b3c4(void *);
extern void func_ov123_0229b364(void *);
extern void func_ov123_0229b228(void *);
extern int func_ov123_0229b33c(void *);
extern void func_ov123_0229b204(void *);
extern int func_ov002_0220acc4(unsigned char *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov123_02299954(void *);
extern void func_ov123_0229c07c(void *);
extern void func_ov123_02299640(void *, int);
extern void func_ov002_02208090(void *, int);

typedef struct {
    unsigned char pad_00[0xa4];
    unsigned char unk_A4;
    unsigned char pad_A5[0x4f8b];
    unsigned char unk_5030[1];
} UnkStruct_0229c470;

void func_ov123_0229c470(UnkStruct_0229c470 *self)
{
    int r;

    func_ov123_0229bf04();
    func_ov123_0229be60(self);
    self->unk_A4 = 0x22;
    func_ov123_0229a278(self, 0);
    func_ov123_0229bdfc(self);

    r = func_0206fca4();
    switch (r) {
        case 2:
            func_ov123_0229b508(self);
            break;
        case 3:
            func_ov123_0229b3c4(self);
            break;
    }

    func_ov123_0229b364(self);
    func_ov123_0229b228(self);
    func_ov123_0229b33c(self);
    func_ov123_0229b204(self);

    func_ov002_0220acc4(self->unk_5030);
    func_ov002_02207f20(self, 0xb, 4, 0, 0x30);

    func_02002708(6);
    func_02002708(4);

    func_ov123_02299954(self);
    func_ov123_0229c07c(self);
    func_ov123_02299640(self, 1);
    func_ov002_02208090(self, 1);
}
