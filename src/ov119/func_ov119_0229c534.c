/* func_ov119_0229c534 @ 0x0229c534, 0x64 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int n);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void func_ov119_0229a410(void *p, int a);
extern int func_ov002_02207f60(void *p);
extern void func_ov002_02208090(void *p, int a);

typedef struct {
    unsigned char pad_00[0x94];
    int unk_94;
} UnkStruct_0229c534;

void func_ov119_0229c534(UnkStruct_0229c534 *param)
{
    func_ov002_02207f20(param, 0xa, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(param, 6, 0, 0);
    func_02002708(4);
    func_ov002_02207e80(param, 4, 0, 0);
    func_ov119_0229a410(param, 1);
    param->unk_94 = func_ov002_02207f60(param);
    func_ov119_0229a410(param, 8);
    func_ov002_02208090(param, 2);
}
