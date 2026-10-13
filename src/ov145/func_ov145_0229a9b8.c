/* func_ov145_0229a9b8 @ 0x0229a9b8, 0x78 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc0];
    unsigned char unk_C0;
    unsigned char unk_C1;
    unsigned char pad_C2[0xb2];
    unsigned char unk_174;
} UnkStruct_0229a9b8;

extern void func_ov145_0229a778(void *);
extern void func_ov145_0229a6c8(void *);
extern void func_ov145_0229996c(void *, int);
extern void func_ov145_0229a678(void *);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_0220ab84(void *, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov145_0229a8e8(void *);
extern void func_ov145_02299658(void *, int);

void func_ov145_0229a9b8(UnkStruct_0229a9b8 *p)
{
    func_ov145_0229a778(p);
    func_ov145_0229a6c8(p);
    p->unk_C0 = 4;
    func_ov145_0229996c(p, 3);
    p->unk_C1 = 3;
    func_ov145_0229a678(p);
    func_ov002_02207f20(p, 10, 4, 0, 40);
    func_02002708(6);
    func_02002708(4);
    func_ov145_0229a8e8(p);
    func_ov145_02299658(p, 1);
    func_ov002_0220ab84(&p->unk_174, 0x65);
    func_ov002_02208090(p, 1);
}
