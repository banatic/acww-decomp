/* func_020ac9cc @ 0x020ac9cc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
} UnkStruct_020ac9cc;

extern void func_0208e7f0(UnkStruct_020ac9cc *p);
extern void func_020edb3c(UnkStruct_020ac9cc *p);
extern unsigned int data_020e4030;

UnkStruct_020ac9cc *func_020ac9cc(UnkStruct_020ac9cc *p)
{
    p->unk_00 = (unsigned int) &data_020e4030;
    func_0208e7f0(p);
    func_020edb3c(p);
    return p;
}
