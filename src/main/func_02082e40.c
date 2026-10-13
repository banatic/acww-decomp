/* func_02082e40 @ 0x02082e40, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02082e40 {
    void *unk_00;
};

extern char data_020e1a7c;
extern void func_020830d0(struct UnkStruct_02082e40 *p);
extern void func_020edb3c(struct UnkStruct_02082e40 *p);

struct UnkStruct_02082e40 *func_02082e40(struct UnkStruct_02082e40 *p)
{
    p->unk_00 = &data_020e1a7c;
    func_020830d0(p);
    func_020edb3c(p);
    return p;
}
