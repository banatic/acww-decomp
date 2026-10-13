/* func_0208fbbc @ 0x0208fbbc, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208fbbc {
    char pad_00[0x13];
    unsigned char unk_13;
};

extern void func_0208fb98(struct UnkStruct_0208fbbc *);

void func_0208fbbc(struct UnkStruct_0208fbbc *p)
{
    if (p->unk_13) {
        func_0208fb98(p);
    }
}
