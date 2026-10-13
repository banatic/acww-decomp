/* func_02083038 @ 0x02083038, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02083038 UnkStruct_02083038;
struct UnkStruct_02083038 {
    void *unk_00;
};

extern char data_020e1a18;
extern void func_020830d0(UnkStruct_02083038 *p);

UnkStruct_02083038 *func_02083038(UnkStruct_02083038 *p)
{
    p->unk_00 = &data_020e1a18;
    func_020830d0(p);
    return p;
}
