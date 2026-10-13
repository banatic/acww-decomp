/* func_ov106_0229c4a0 @ 0x0229c4a0, 0x84 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c4a0 {
    unsigned char pad_00[0xb8];
    unsigned char flag;
};

extern void func_ov106_0229c344(struct UnkStruct_0229c4a0 *p, int value);
extern int func_ov106_0229d3a0(struct UnkStruct_0229c4a0 *p, unsigned char value);
extern void func_ov106_0229c638(struct UnkStruct_0229c4a0 *p, int a2, int a3);
extern int func_ov106_0229d390(struct UnkStruct_0229c4a0 *p, unsigned char value);
extern void func_ov106_0229c54c(struct UnkStruct_0229c4a0 *p, int a2, int a3);
extern int func_ov106_0229d384(struct UnkStruct_0229c4a0 *p, unsigned char value);
extern void func_ov106_0229c524(struct UnkStruct_0229c4a0 *p, int a2);

int func_ov106_0229c4a0(struct UnkStruct_0229c4a0 *p, int a2, int a3)
{
    unsigned char old = p->flag;

    func_ov106_0229c344(p, 0x30);
    if (a2 == 0) {
        return 0;
    }
    if (func_ov106_0229d3a0(p, p->flag)) {
        func_ov106_0229c638(p, a2, a3);
    } else if (func_ov106_0229d390(p, p->flag)) {
        func_ov106_0229c54c(p, a2, a3);
    } else if (func_ov106_0229d384(p, p->flag)) {
        func_ov106_0229c524(p, a2);
    }
    return old != p->flag;
}
