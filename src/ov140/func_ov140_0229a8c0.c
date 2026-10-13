/* func_ov140_0229a8c0 @ 0x0229a8c0, 0x54 bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov140_0229a590(void *);
extern void func_ov002_02208098(void *, unsigned char);
extern int func_ov140_02299fb0(void *, int);
extern void func_ov140_02299f90(void *, int);
extern void func_ov140_0229a614(void *);

typedef struct {
    unsigned char pad_00[0x8AE];
    unsigned char unk_8AE;
    unsigned char pad_8AF[0x2D];
    unsigned char unk_8DC;
    unsigned char pad_8DD[0x9AF];
    unsigned char unk_128C;
} UnkStruct_0229a8c0;

void func_ov140_0229a8c0(UnkStruct_0229a8c0 *obj)
{
    if (func_0208e484(&obj->unk_128C) == 0) {
        return;
    }
    func_ov140_0229a590(obj);
    func_ov002_02208098(obj, obj->unk_8AE);
    if (func_ov140_02299fb0(obj, 8) == 0) {
        return;
    }
    func_ov140_02299f90(obj, 8);
    obj->unk_8DC = 8;
    func_ov140_0229a614(obj);
}
