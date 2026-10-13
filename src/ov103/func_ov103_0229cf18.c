/* func_ov103_0229cf18 @ 0x0229cf18, 0x88 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x218c];
    unsigned char sub;
    unsigned char pad_218D[0xa03];
    int unk_2B90;
    int unk_2B94;
    unsigned char pad_2B98[0x209];
    unsigned char unk_2DA1;
    unsigned char unk_2DA2;
} UnkStruct_0229cf18;

extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;

extern void func_ov002_02208098(void *ptr, int val);
extern void func_ov002_02207cf8(void *ptr);
extern int func_ov103_0229ccb4(UnkStruct_0229cf18 *s, unsigned char c);
extern int func_ov103_0229cc80(UnkStruct_0229cf18 *s, unsigned char c);
extern int func_ov103_0229cc3c(UnkStruct_0229cf18 *s, unsigned char c);
extern void func_ov103_0229c2d4(UnkStruct_0229cf18 *s, int val);
extern void func_ov103_0229c2e4(UnkStruct_0229cf18 *s, int val);

void func_ov103_0229cf18(UnkStruct_0229cf18 *s, unsigned char param2)
{
    unsigned char g1, g2;
    s->unk_2DA1 = param2;
    func_ov002_02208098(s, 1);
    g1 = data_021f6c58;
    g2 = data_021f6c54;
    s->unk_2B90 = func_ov103_0229ccb4(s, s->unk_2DA1) - g1;
    s->unk_2B94 = func_ov103_0229cc80(s, s->unk_2DA1) - g2;
    s->unk_2DA2 = param2;
    func_ov002_02207cf8(&s->sub);
    if (func_ov103_0229cc3c(s, param2) != 0) {
        func_ov103_0229c2d4(s, 4);
    } else {
        func_ov103_0229c2e4(s, 4);
    }
}
