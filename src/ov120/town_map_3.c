/* town_map_3: 3 functions, module ov120
 * mwccarm 1.2/base -O4,s
 * func_ov120_0229a730 @ 0x0229a730, 0x78 bytes, Thumb
 * func_ov120_0229a710 @ 0x0229a710, 0x20 bytes, Thumb
 * func_ov120_0229a6f0 @ 0x0229a6f0, 0x20 bytes, Thumb
 */

typedef struct {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x1c];
    unsigned char unk_AA;
    char pad_AB[0x611];
    int unk_6BC;
} UnkStruct_0229a730;

extern int func_ov120_0229a448(void *obj, int a);
extern int func_ov120_0229a81c(void *obj);
extern int func_ov120_0229a7cc(void *obj);
extern void func_ov120_0229a428(void *obj, int a);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a05c(void *ptr, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *obj, unsigned char value);
extern void func_ov002_0220a1dc(void *);
extern void func_ov002_0220a164(void *);

void func_ov120_0229a730(UnkStruct_0229a730 *obj)
{
    if (func_ov120_0229a448(obj, 0x4000)) {
        int a = func_ov120_0229a81c(obj);
        int b = func_ov120_0229a7cc(obj);
        func_ov002_0220a0b4(&obj->unk_6BC, a, b);
        func_ov120_0229a428(obj, 0x4000);
    } else {
        int a = func_ov120_0229a81c(obj);
        int b = func_ov120_0229a7cc(obj);
        func_ov002_0220a05c(&obj->unk_6BC, a, b, 3, 1);
        obj->unk_AA = obj->unk_8D;
        func_ov002_02208098(obj, 3);
    }
}

void func_ov120_0229a710(void *self)
{
    func_ov002_0220a1dc((char *) self + 0x6bc);
    func_ov002_02208098(self, 4);
}

void func_ov120_0229a6f0(void *self)
{
    func_ov002_0220a164((char *) self + 0x6bc);
    func_ov002_02208098(self, 5);
}
