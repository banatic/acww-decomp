/* func_ov101_0229dad4 @ 0x0229dad4, 0x8c bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov101_0229d850(void *);
extern int func_ov002_0220ab84(void *, int);
extern void func_ov094_0229ad20(void *);
extern void func_ov101_0229cc80(void *);
extern void func_ov094_0229b2b0(void *);
extern void func_ov094_0229b794(void *, int);
extern void func_ov002_02207f20(void *, int, int, int, int);
extern void func_02002708(int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov101_0229c29c(void *, int);
extern int func_ov002_02207f60(void *);

typedef struct UnkStruct_0229dad4 {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x58];
    int unk_F4;
    char pad_F8[0xa5c];
    int unk_B54;
    char pad_B58[0x1cb8];
    int unk_2810;
} UnkStruct_0229dad4;

void func_ov101_0229dad4(UnkStruct_0229dad4 *obj)
{
    int zero = 0;
    func_ov101_0229d850(obj);
    func_ov002_0220ab84(&obj->unk_2810, 0x65);
    func_ov094_0229ad20(&obj->unk_F4);
    func_ov101_0229cc80(obj);
    func_ov094_0229b2b0(&obj->unk_B54);
    func_ov094_0229b794(&obj->unk_B54, 0xf);
    func_ov002_02207f20(obj, 8, zero, zero, 0x30);
    func_02002708(6);
    func_ov002_02207e80(obj, 6, 0, -16);
    func_ov002_02208090(obj, 2);
    func_ov101_0229c29c(obj, 1);
    func_ov101_0229c29c(obj, 2);
    obj->unk_98 = func_ov002_02207f60(obj);
}
