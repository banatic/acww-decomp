/* func_0208b900 @ 0x0208b900, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208b900 {
    unsigned char pad_00[0x80];
    unsigned char unk_80;
};

extern int func_0208b79c(struct UnkStruct_0208b900 *p);
extern void func_0208b8d0(struct UnkStruct_0208b900 *p);
extern void func_0208b748(struct UnkStruct_0208b900 *p, int value);

void func_0208b900(struct UnkStruct_0208b900 *p)
{
    int value;

    value = func_0208b79c(p);
    if (p->unk_80 == 0) {
        func_0208b8d0(p);
        value = 0;
    }
    func_0208b748(p, value);
}
