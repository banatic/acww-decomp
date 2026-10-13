/* func_ov134_0229b034 @ 0x0229b034, 0xd4 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229a8e8(void *);
extern int func_ov134_022995c0(void *, int);
extern int func_ov134_0229b884(void *, int);
extern void func_02004658(int);

typedef struct {
    unsigned char pad_00[0x84];
    int unk_84;
    int unk_88;
} UnkStruct_0229b034;

int func_ov134_0229b034(void *p)
{
    UnkStruct_0229b034 *sp;
    int a;

    func_ov134_0229a8e8(p);
    if (func_ov134_022995c0(p, 0x40) != 0 && func_ov134_022995c0(p, 0x10) != 0) {
        sp = (UnkStruct_0229b034 *) p;
        a = func_ov134_0229b884(p, 4);
        a += 0x3c * func_ov134_0229b884(p, 3);
        sp->unk_88 = a;
        while (sp->unk_88 > sp->unk_84) {
            sp->unk_88 -= 0x2d0;
        }
        func_02004658(0x54);
        return 1;
    }
    if (func_ov134_022995c0(p, 0x80) != 0 && func_ov134_022995c0(p, 0x20) != 0) {
        sp = (UnkStruct_0229b034 *) p;
        a = func_ov134_0229b884(p, 4);
        a += 0x3c * func_ov134_0229b884(p, 3);
        sp->unk_88 = a;
        while (sp->unk_88 < sp->unk_84) {
            sp->unk_88 += 0x2d0;
        }
        func_02004658(0x54);
        return 1;
    }
    return 0;
}
