/* func_0208fd68 @ 0x0208fd68, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208fd68 {
    unsigned int unk_00;
};

extern void func_0208fb24(struct UnkStruct_0208fd68 *p);
extern void func_0208af00(struct UnkStruct_0208fd68 *p);

extern unsigned char data_020e23e4[];

struct UnkStruct_0208fd68 *func_0208fd68(struct UnkStruct_0208fd68 *p)
{
    p->unk_00 = (unsigned int) data_020e23e4;
    func_0208fb24(p);
    func_0208af00(p);
    return p;
}
