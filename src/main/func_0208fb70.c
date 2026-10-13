/* func_0208fb70 @ 0x0208fb70, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208fb70 {
    unsigned char pad_00[0x12];
    unsigned char unk_12;
    unsigned char unk_13;
};

extern void func_0208fb24(struct UnkStruct_0208fb70 *);
extern void func_02001ba4(int);
extern void func_0208fbd0(struct UnkStruct_0208fb70 *);

void func_0208fb70(struct UnkStruct_0208fb70 *p)
{
    if (p->unk_13 != 0) {
        return;
    }
    func_0208fb24(p);
    if (p->unk_12 != 0) {
        func_02001ba4(4);
    }
    func_0208fbd0(p);
}
