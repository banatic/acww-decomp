/* carried_letters_7: 4 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229cfa0 @ 0x0229cfa0, 0x20 bytes, Thumb
 * func_ov103_0229cf18 @ 0x0229cf18, 0x88 bytes, Thumb
 * func_ov103_0229ced0 @ 0x0229ced0, 0x48 bytes, Thumb
 * func_ov103_0229ce84 @ 0x0229ce84, 0x4c bytes, Thumb
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

extern int func_0206fe60(void);
extern void func_ov103_0229cffc(int);
extern void func_ov103_0229cfc0(int);
extern unsigned char data_021f6c58;
extern unsigned char data_021f6c54;
extern unsigned char *func_ov002_02208098(void *ptr, unsigned char value);
extern void func_ov002_02207cf8(void *ptr);
extern int func_ov103_0229ccb4(UnkStruct_0229cf18 *s, unsigned char c);
extern int func_ov103_0229cc80(UnkStruct_0229cf18 *s, unsigned char c);
extern int func_ov103_0229cc3c(UnkStruct_0229cf18 *s, unsigned char c);
extern void func_ov103_0229c2d4(UnkStruct_0229cf18 *s, int val);
extern void func_ov103_0229c2e4(UnkStruct_0229cf18 *s, int val);
extern int func_ov002_02207d24(char *addr, int arg);
extern void func_ov103_0229c910(void *p, int val);
extern void func_ov103_0229c9c8(void *p);
extern void func_ov103_0229c994(unsigned char *base);

void func_ov103_0229cfa0(int r0)
{
    int r4 = r0;
    if (func_0206fe60() != 0) {
        func_ov103_0229cffc(r4);
    } else {
        func_ov103_0229cfc0(r4);
    }
}

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

void func_ov103_0229ced0(void *p, int val)
{
    ((unsigned char *) p)[0x2da3] = val;
    func_ov002_02207d24((char *) p + 0x218c, 1);
    func_ov103_0229c910(p, val);
    if (((unsigned char *) p)[0x2da0] == 1) {
        func_ov002_02208098(p, 2);
    }
    func_ov103_0229c9c8(p);
}

void func_ov103_0229ce84(unsigned char *base, int val)
{
    base[0x2da3] = (unsigned char) val;
    func_ov002_02207d24((char *) (base + 0x218c), 1);
    func_ov103_0229c910((void *) base, val);
    if (base[0x2da0] == 1) {
        base[0x2da7] = 6;
    }
    func_ov103_0229c994(base);
}
