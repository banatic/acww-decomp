/* func_ov096_0229fa44 @ 0x0229fa44, 0xb4 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229fa44 {
    unsigned char pad_00[0x9c];
    int unk_9C;
    int unk_A0;
    unsigned char pad_A4[0xb2 - 0xa4];
    unsigned char unk_B2;
    unsigned char unk_B3;
    unsigned char pad_B4[0xc2 - 0xb4];
    unsigned char unk_C2;
    unsigned char pad_C3[0x2418 - 0xc3];
    unsigned char unk_2418;
} UnkStruct_0229fa44;

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov096_0229f290(UnkStruct_0229fa44 *self, int b);
extern int func_ov096_0229f200(UnkStruct_0229fa44 *self, int b);
extern void func_ov002_02207cf8(unsigned char *p);
extern void func_ov002_02207d00(unsigned char *p);
extern void func_ov096_0229faf8(UnkStruct_0229fa44 *self);
extern int func_ov096_0229f1a8(UnkStruct_0229fa44 *self, int arg);
extern void func_ov096_0229c2dc(UnkStruct_0229fa44 *self, int arg);
extern void func_ov096_0229c2ec(UnkStruct_0229fa44 *self, int arg);
extern int func_ov096_0229f830(UnkStruct_0229fa44 *self, int arg);
extern void func_ov096_0229c414(UnkStruct_0229fa44 *self);
extern void func_ov094_022999cc(void);

void func_ov096_0229fa44(UnkStruct_0229fa44 *self, int arg)
{
    unsigned char g1;
    unsigned char g2;

    self->unk_B2 = (unsigned char) arg;
    func_ov002_02208098((void *) (self), 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;
    self->unk_9C = func_ov096_0229f290(self, self->unk_B2) - g1;
    self->unk_A0 = func_ov096_0229f200(self, self->unk_B2) - g2;
    self->unk_B3 = (unsigned char) arg;
    func_ov002_02207cf8(&self->unk_2418);
    func_ov002_02207d00(&self->unk_2418);
    self->unk_C2 = 2;
    func_ov096_0229faf8(self);
    if (func_ov096_0229f1a8(self, arg) != 0) {
        func_ov096_0229c2dc(self, 4);
    } else {
        func_ov096_0229c2ec(self, 4);
    }
    if (func_ov096_0229f830(self, arg) == 0 && arg != 0x24) {
        func_ov096_0229c414(self);
    }
    func_ov094_022999cc();
}
