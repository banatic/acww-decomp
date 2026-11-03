/* mailbox_scene_12: 3 functions, module ov106
 * mwccarm 1.2/base -O4,s
 * func_ov106_0229f41c @ 0x0229f41c, 0x10c bytes, Thumb
 * func_ov106_0229f3fc @ 0x0229f3fc, 0x20 bytes, Thumb
 * func_ov106_0229f3e0 @ 0x0229f3e0, 0x1a bytes, Thumb
 */

extern void *func_ov002_02207f80(int);
extern void *func_ov002_0220830c(void *);
extern void *func_020b9af4(void *);
extern void *func_ov094_0229b000(void *);
extern void func_ov094_0229bc3c(void *);
extern void *func_ov094_0229a2ec(void *);
extern void *func_ov002_02207e40(void *);
extern void func_ov002_02209e44(void *);
extern void *func_ov002_02209ccc(void *);
extern void *func_ov002_02209b14(void *);
extern void *func_ov002_0220ba24(void *);
extern void *func_0206e388(void *);
extern void *func_ov002_0220b47c(void *);
extern void *func_ov002_0220b008(void *);
extern void func_02066694(void *);
extern void func_02066688(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern char data_ov106_0229f6e0;
extern void func_ov106_0229ea08(void *);
extern void func_ov002_02208090(void *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern int func_020ee45c(void *argument0);
extern void func_ov092_0229929c(void *argument0);
extern void func_ov106_0229e9c0(void *);

void *func_ov106_0229f41c(void)
{
    void *p;

    p = func_ov002_02207f80(0x4380);
    if (p) {
        char *r4;
        char *r6;

        func_ov002_0220830c(p);
        *(void **) p = &data_ov106_0229f6e0;
        r4 = (char *) p + 0xc0;
        r6 = (char *) p + 0xf8;
        do {
            func_020b9af4(r4);
            r4 += 0x38;
        } while (r4 != r6);
        func_ov094_0229b000(r6);
        func_ov094_0229bc3c((char *) p + 0xb58);
        func_ov094_0229a2ec((char *) p + 0xb80);
        func_ov002_02207e40((char *) p + 0x21b8);
        func_ov002_02209e44((char *) p + 0x2288);
        func_ov002_02209ccc((char *) p + 0x22a0);
        func_ov002_02209b14((char *) p + 0x2304);
        func_ov002_0220ba24((char *) p + 0x26f8);
        func_0206e388((char *) p + 0x2814);
        func_ov002_0220b47c((char *) p + 0x2b3c);
        __cxa_vec_ctor((char *) p + 0x2bb4, 10, 0x100, func_02066694, func_02066688);
        __cxa_vec_ctor((char *) p + 0x35b4, 10, 0x100, func_02066694, func_02066688);
        func_ov002_0220b008((char *) p + 0x3fb4);
        func_02066694((char *) p + 0x4180);
        func_02066694((char *) p + 0x4280);
    }
    return p;
}

int func_ov106_0229f3fc(void *p)
{
    func_ov106_0229ea08(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0((void *) (p), 0);
    return 1;
}

int func_ov106_0229f3e0(void *a)
{

    func_ov092_0229929c((void *) func_020ee45c(a));
    func_ov106_0229e9c0(a);
    return 1;
}
