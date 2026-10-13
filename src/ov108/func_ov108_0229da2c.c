/* func_ov108_0229da2c @ 0x0229da2c, 0x60 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *, int);
extern void func_ov108_0229c794(void *);
extern int func_020ee45c(void *);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(void *, int, int, int, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern void func_ov002_02208090(void *, int);
extern int func_ov002_02207f60(void *);

typedef struct {
    char pad_00[0x98];
    int unk_98;
    char pad_9C[0x2314];
    int unk_23B0;
} UnkStruct_0229da2c;

void func_ov108_0229da2c(UnkStruct_0229da2c *obj)
{
    func_ov002_02207d24(&obj->unk_23B0, 1);
    func_ov108_0229c794(obj);
    func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
    func_ov002_02207f04(obj, 8, 0, 0, 0x30);
    func_ov002_02207e80(obj, 6, 0, ~0xf);
    func_ov002_02208090(obj, 4);
    obj->unk_98 = func_ov002_02207f60(obj);
}
