/* func_ov142_0229b500 @ 0x0229b500, 0x26 bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229b500 {
    unsigned char pad_00[0xba];
    unsigned char unk_BA;
    unsigned char pad_BB[0xe8 - 0xbb];
    unsigned char unk_E8;
} UnkStruct_0229b500;

extern int func_ov002_02209f64(unsigned char *ptr);
extern void func_ov002_02208098(UnkStruct_0229b500 *p, unsigned char b);
extern void func_ov142_0229bd90(UnkStruct_0229b500 *p);

void func_ov142_0229b500(UnkStruct_0229b500 *p)
{
    if (func_ov002_02209f64(&p->unk_E8) == 0) {
        func_ov002_02208098(p, p->unk_BA);
        func_ov142_0229bd90(p);
    }
}
