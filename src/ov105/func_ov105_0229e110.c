/* func_ov105_0229e110 @ 0x0229e110, 0x70 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229e110 {
    char pad_00[0x2BA];
    unsigned char unk_2BA;
    char pad_2BB[0x2C0 - 0x2BA - 1];
    unsigned char unk_2C0;
    char pad_2C1[0x24A4 - 0x2C0 - 1];
    char unk_24A4;
};

extern int func_0208e484(void *);
extern int func_ov105_0229d750(struct UnkStruct_0229e110 *, int);
extern void func_ov105_0229c668(struct UnkStruct_0229e110 *);
extern int func_ov105_0229d73c(struct UnkStruct_0229e110 *, int);
extern void func_ov105_0229cd5c(struct UnkStruct_0229e110 *);
extern void func_ov105_0229c3ec(struct UnkStruct_0229e110 *);

void func_ov105_0229e110(struct UnkStruct_0229e110 *p)
{
    if (func_0208e484(&p->unk_24A4)) {
        if (func_ov105_0229d750(p, p->unk_2BA)) {
            func_ov105_0229c668(p);
        } else if (func_ov105_0229d73c(p, p->unk_2BA)) {
            int v = p->unk_2BA - 0x3e;
            if (v == p->unk_2C0) {
                func_ov105_0229cd5c(p);
            } else {
                p->unk_2C0 = v;
                func_ov105_0229c3ec(p);
            }
        } else {
            func_ov105_0229cd5c(p);
        }
    }
}
