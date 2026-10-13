/* func_ov103_0229ca48 @ 0x0229ca48, 0x54 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x218c];
    void *obj_218c;
    unsigned char pad_2190[0xC12];
    unsigned char unk_2DA2;
    unsigned char pad_2DA3;
    unsigned char unk_2DA4;
} UnkStruct_0229ca48;

extern int func_ov103_0229cdfc(const UnkStruct_0229ca48 *, unsigned char);
extern int func_ov103_0229cc08(const UnkStruct_0229ca48 *, unsigned char);
extern void func_ov002_02207cf0(void *);
extern void func_ov002_02207cf8(void *);

void func_ov103_0229ca48(UnkStruct_0229ca48 *p)
{
    if (func_ov103_0229cdfc(p, p->unk_2DA4) != 0) {
        if (func_ov103_0229cc08(p, p->unk_2DA4) != 0) {
            func_ov002_02207cf0(&p->obj_218c);
            return;
        } else {
            p->unk_2DA2 = p->unk_2DA4;
            func_ov002_02207cf8(&p->obj_218c);
            return;
        }
    } else {
        func_ov002_02207cf0(&p->obj_218c);
        return;
    }
}
