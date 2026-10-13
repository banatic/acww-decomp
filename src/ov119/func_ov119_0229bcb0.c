/* func_ov119_0229bcb0 @ 0x0229bcb0, 0x48 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229bcb0 {
    char pad_00[0xb8];
    int unk_B8;
};

extern void func_02002708(int);
extern int func_0206fe60(void);
extern void func_ov119_0229bc30(struct UnkStruct_0229bcb0 *);
extern void func_ov119_0229b7e8(struct UnkStruct_0229bcb0 *);
extern void func_ov119_0229ae84(struct UnkStruct_0229bcb0 *, int);

void func_ov119_0229bcb0(struct UnkStruct_0229bcb0 *p)
{
    if (p->unk_B8 < 5) {
        func_02002708(4);
        p->unk_B8++;
        func_ov119_0229ae84(p, p->unk_B8);
    } else {
        if (func_0206fe60()) {
            func_ov119_0229bc30(p);
        } else {
            func_ov119_0229b7e8(p);
        }
    }
}
