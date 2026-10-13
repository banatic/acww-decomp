/* func_ov102_0229e458 @ 0x0229e458, 0x80 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229df94(void *);
extern void func_ov094_0229ad20(void *);
extern void func_ov102_0229d0ec(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov094_0229b794(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov102_0229c298(void *, int);
extern int func_ov002_02207f60(void *);

struct UnkStruct_0229e458 {
    char pad_00[0xcc];
    int unk_CC;
    char pad_D0[0xb2c - 0xcc - 4];
    int unk_B2C;
    char pad_B30[0x24d0 - 0xb2c - 4];
    int unk_24D0;
};

void func_ov102_0229e458(struct UnkStruct_0229e458 *ptr)
{
    func_ov102_0229df94(ptr);
    func_ov094_0229ad20(&ptr->unk_CC);
    func_ov102_0229d0ec(ptr);
    func_ov094_0229b2b0(&ptr->unk_B2C);
    func_ov094_0229b794(&ptr->unk_B2C, 0xf);
    func_ov002_02207f20(ptr, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(ptr, 6, 0, 0);
    func_ov002_02208090(ptr, 2);
    func_ov102_0229c298(ptr, 1);
    func_ov102_0229c298(ptr, 2);
    ptr->unk_24D0 = func_ov002_02207f60(ptr);
}
