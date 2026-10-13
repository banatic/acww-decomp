/* func_ov068_0226b0ec @ 0x0226b0ec, 0xe4 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(unsigned char *, int);
extern int func_02019de8(unsigned char *);
extern void func_0201c3f4(unsigned char *, int);
extern void func_0202e118(unsigned short *, unsigned char *);
extern void func_ov068_0226cce8(unsigned char *, unsigned char *, int);
extern void func_ov068_0226cce4(unsigned char *, int);
extern void func_02013bb0(unsigned char *, unsigned char *);

struct PField {
    unsigned char pad_00[0x190];
    unsigned int unused0 : 12;
    unsigned int mode : 16;
    unsigned int unused1 : 4;
};

void func_ov068_0226b0ec(unsigned char *obj, unsigned char *p)
{
    unsigned short local;
    int v;

    if (func_020164a0(p + 0x334, 0) == 0x3d) {
        if (func_02019de8(p + 0x564) != 0) {
            p[0x511] = 1;
            func_0201c3f4(p, 0xd00);
            *(unsigned int *) (p + 0x4e8) &= ~2;
            func_0202e118(&local, p);
            if (local != 0xfff1) {
                func_ov068_0226cce8(obj, p, 0xf);
                func_ov068_0226cce4(obj, 0);
                *(short *) (obj + 0x34) = (short) (*(short *) (obj + 0x34) + 0x12c);
            } else {
                func_ov068_0226cce8(obj, p, 0);
            }
        } else {
            v = ((struct PField *) p)->mode;
            switch (v) {
                case 0x0d:
                case 0x11:
                case 0x17:
                case 0x1c:
                case 0x25:
                case 0x28:
                    func_02013bb0(p + 0x558, p);
                    break;
            }
        }
    }
}
