/* func_ov088_02278afc @ 0x02278afc, 0xa8 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern void func_020160b4(void *p);
extern int func_020ab504(void);
extern unsigned char func_0203fa14(int _x);
extern void func_020683e4(void *a, int b, unsigned char *c, unsigned char *d);
extern void func_0206844c(void *a, unsigned char *b, unsigned char *c);
extern void func_ov088_02278a54(void *a, int b, unsigned char c);
extern unsigned char data_ov088_02279d98[];
extern unsigned char data_ov088_02279da8[];

typedef struct {
    unsigned char pad_00[0x1e];
    unsigned char mode;
    unsigned char pad_1F[0x21];
    void *obj_40;
    unsigned char pad_44[0x74];
    void *obj_b8;
    unsigned char unk_BC;
} UnkStruct_02278afc;

void func_ov088_02278afc(UnkStruct_02278afc *p)
{
    unsigned char r1;
    unsigned char buf[3];
    int r4;
    unsigned char *d98;

    func_020160b4(p);
    r4 = func_020ab504();

    d98 = data_ov088_02279d98;
    r1 = 0xff;

    switch (p->mode) {
        case 0x17:
        case 0x18: {
            unsigned char v = *((unsigned char *) p + r4 + 0xdb);
            r1 = (unsigned char) (v + 0x1c);
            p->unk_BC = v;
            break;
        }
        case 0x1a:
            if (r4 == 4) {
                r1 = 0x1b;
                break;
            }
            buf[0] = func_0203fa14(r4);
            func_020683e4(p->obj_40, 1, buf, data_ov088_02279da8);
            func_ov088_02278a54(p->obj_b8, r4, p->unk_BC);
            buf[1] = p->unk_BC;
            func_020683e4(p->obj_40, 0, &buf[1], data_ov088_02279da8);
            r1 = 0x1c;
            break;
        default:
            break;
    }

    if (r1 != 0xff) {
        buf[2] = r1;
        func_0206844c(p->obj_40, &buf[2], d98);
    }
}