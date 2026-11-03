/* order_catalog_scene_4: 2 functions, module ov142
 * mwccarm 1.2/base -O4,s
 * func_ov142_0229c1e8 @ 0x0229c1e8, 0x1e bytes, Thumb
 * func_ov142_0229c1cc @ 0x0229c1cc, 0x1a bytes, Thumb
 */

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229c1e8;

extern void func_ov142_0229ba64(UnkStruct_0229c1e8 *);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);
extern int func_020ee45c(int x);
extern void func_ov092_0229929c(int x);
extern void func_ov142_0229ba18(int x);

int func_ov142_0229c1e8(UnkStruct_0229c1e8 *self)
{
    func_ov142_0229ba64(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}

int func_ov142_0229c1cc(int x)
{
    func_ov092_0229929c(func_020ee45c(x));
    func_ov142_0229ba18(x);
    return 1;
}
