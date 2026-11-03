/* star_view_4: 4 functions, module ov128
 * mwccarm 1.2/base -O4,s
 * func_ov128_0229c830 @ 0x0229c830, 0x60 bytes, Thumb
 * func_ov128_0229c810 @ 0x0229c810, 0x1e bytes, Thumb
 * func_ov128_0229c7f4 @ 0x0229c7f4, 0x1a bytes, Thumb
 * func_ov128_0229c794 @ 0x0229c794, 0x60 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229c810;

extern void *func_ov002_02207f80(int size);
extern void *func_ov002_0220830c(void *argument0);
extern void *func_ov002_0220b3c4(void *p);
extern void *func_ov002_02209ccc(void *p);
extern void *func_020b18ac(void *p);
extern int func_ov127_0229a0ec(void *p);
extern void *func_02070c08(void *p);
extern int data_ov128_0229cbc0;
extern void func_ov128_0229c408(UnkStruct_0229c810 *s);
extern unsigned char *func_ov002_022080a0(void *, unsigned char);
extern void *func_020ee45c(void *p);
extern void func_ov092_0229929c(void *p);
extern void func_ov128_0229c398(void *p);
extern int func_0206fe54(void);
extern void func_ov128_0229b9f0(void *);
extern int func_ov128_0229b7ec(void *, int);
extern void func_ov002_0220b1a4(void *, int, int, int);
extern void func_ov127_02299de8(void *, int, int);
extern void func_ov128_0229bb60(void *, int);

void *func_ov128_0229c830(void)
{
    void *p = func_ov002_02207f80(0x2d74);
    if (p != 0) {
        func_ov002_0220830c(p);
        *(void **) p = &data_ov128_0229cbc0;
        func_ov002_0220b3c4((char *) p + 0x94);
        func_ov002_02209ccc((char *) p + 0x110);
        func_020b18ac((char *) p + 0x174);
        func_ov127_0229a0ec((char *) p + 0x4a4);
        func_02070c08((char *) p + 0x2cdc);
    }
    return p;
}

int func_ov128_0229c810(UnkStruct_0229c810 *s)
{
    func_ov128_0229c408(s);
    s->unk_8C = 0;
    func_ov002_022080a0(s, 0);
    return 1;
}

int func_ov128_0229c7f4(void *arg)
{
    func_ov092_0229929c(func_020ee45c(arg));
    func_ov128_0229c398(arg);
    return 1;
}

int func_ov128_0229c794(void *param)
{
    func_0206fe54();
    func_ov128_0229b9f0(param);
    if (func_ov128_0229b7ec(param, 1)) {
        func_ov002_0220b1a4((char *) param + 0x94, 0, (*(int *) ((char *) param + 0x2d50)) >> 2, 1);
        func_ov127_02299de8((char *) param + 0x4a4, *(int *) ((char *) param + 0x2d50), 6);
    }
    if (func_ov128_0229b7ec(param, 1)) {
        func_ov128_0229bb60(param, *(int *) ((char *) param + 0x2d50));
    }
    return 1;
}
