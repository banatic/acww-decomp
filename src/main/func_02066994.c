/* func_02066994 @ 0x02066994, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02066994 {
    void *unk_00;
    unsigned char pad_04[0x1c];
    void *unk_20;
};

extern void func_02066a84(void *p);
extern void func_020a8188(void *p);
extern int data_020df008;

void *func_02066994(struct UnkStruct_02066994 *p)
{
    p->unk_00 = &data_020df008;
    func_02066a84(&p->unk_20);
    func_020a8188(p);
    return p;
}
