/* func_ov003_022220a4 @ 0x022220a4, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct In {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
};
struct UnkStruct_022220a4 {
    char pad_00[0x18];
    unsigned int unk_18;
    unsigned int unk_1C;
    unsigned int unk_20;
    char pad_24[0x0c];
    unsigned int unk_30;
    unsigned int unk_34;
    unsigned int unk_38;
    unsigned int unk_3C;
    unsigned int unk_40;
    unsigned int unk_44;
    char pad_48[0x18];
    char data[0x7f];
};
extern int func_020044c0(int, int, int, int);
extern void func_ov003_02222aa4(struct UnkStruct_022220a4 *s);
extern void func_02044534(void);
void func_ov003_022220a4(struct UnkStruct_022220a4 *s, void *unused, struct In *t)
{
    s->unk_30 = 0;
    s->unk_34 = 0x800;
    s->unk_38 = 0x300;
    s->unk_18 = t->unk_00;
    s->unk_1C = t->unk_04;
    s->unk_20 = t->unk_08;
    s->unk_3C = 0x1000;
    s->unk_40 = 0x1000;
    s->unk_44 = 0x1000;
    func_020044c0((int) (s->data), (int) (0x7d6), (int) (0x7f), 0);
    ((void) (func_ov003_02222aa4(s)), func_02044534());
}
