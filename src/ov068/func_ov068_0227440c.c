/* func_ov068_0227440c @ 0x0227440c, 0x84 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_02015de4(void *, void *, int, int);
extern void *func_02062fbc(void *);
extern void *func_02062e50(void *);
extern void func_020a8874(void *, void *, int);
extern int func_020a8a70(void *, void *, int, int);
extern void func_020683b4(void *, int, void *, int);
extern void *func_02062e00(void *);
extern void *func_02062f4c(void *);

struct UnkStruct_0227440c {
    char b[0x28];
};
struct UnkStruct_0227440c_2 {
    char b[0x24];
};
struct UnkStruct_0227440c_3 {
    char pad_00[0x1e];
    unsigned char unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[0xb4 - 0x44];
    char *unk_B4;
};

void func_ov068_0227440c(struct UnkStruct_0227440c_3 *o)
{
    unsigned short h[2];
    struct UnkStruct_0227440c a;
    struct UnkStruct_0227440c_2 c;
    switch (o->unk_1E) {
        case 0xc:
        case 0xd:
            h[0] = *(unsigned short *) (o->unk_B4 + 0x652);
            func_02015de4(o, h, 1, 7);
            break;
        case 0xb:
            func_02062fbc(&a);
            func_02062e50(&c);
            func_020a8874(&c, o->unk_B4 + 0x734, 0xa);
            func_020a8a70(&a, &c, 0, 0);
            func_020683b4(o->unk_40, 0, &a, 7);
            func_02062e00(&c);
            func_02062f4c(&a);
            break;
    }
}
