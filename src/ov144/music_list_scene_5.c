/* music_list_scene_5: 2 functions, module ov144
 * mwccarm 1.2/base -O4,s
 * func_ov144_0229b270 @ 0x0229b270, 0x1e bytes, Thumb
 * func_ov144_0229b254 @ 0x0229b254, 0x1a bytes, Thumb
 */

typedef struct {
    char pad_00[0x8c];
    char unk_8C;
} UnkStruct_0229b270;

extern void func_ov144_0229ae24(void *);
extern unsigned char *func_ov002_022080a0(void *, unsigned char arg1);
extern int func_020ee45c(void *arg0);
extern void func_ov092_0229929c(void *);
extern void func_ov144_0229adf0(void *p);

int func_ov144_0229b270(UnkStruct_0229b270 *self)
{
    func_ov144_0229ae24(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self, 0);
    return 1;
}

int func_ov144_0229b254(void *p)
{
    func_ov092_0229929c((void *) func_020ee45c((void *) p));
    func_ov144_0229adf0(p);
    return 1;
}
