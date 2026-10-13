/* func_ov108_0229c9d8 @ 0x0229c9d8, 0x54 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c9d8 {
    char pad_00[0x2ae];
    unsigned char unk_2AE;
    char pad_2AF;
    unsigned char unk_2B0;
};

extern int func_ov108_0229cd70(struct UnkStruct_0229c9d8 *p, unsigned char b);
extern int func_ov108_0229cb54(struct UnkStruct_0229c9d8 *p, unsigned char b);
extern void func_ov002_02207cf0(void *p);
extern void func_ov002_02207cf8(void *p);

void func_ov108_0229c9d8(struct UnkStruct_0229c9d8 *p)
{
    if (func_ov108_0229cd70(p, p->unk_2B0) != 0) {
        if (func_ov108_0229cb54(p, p->unk_2B0) != 0) {
            func_ov002_02207cf0((char *) p + 0x23b0);
        } else {
            p->unk_2AE = p->unk_2B0;
            func_ov002_02207cf8((char *) p + 0x23b0);
        }
    } else {
        func_ov002_02207cf0((char *) p + 0x23b0);
    }
}
