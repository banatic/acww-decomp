/* func_020f2590 @ 0x020f2590, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *p);
extern int data_0213ef4c;

struct UnkStruct_020f2590 {
    int *unk_00;
    char unk_04;
};

struct UnkStruct_020f2590 *func_020f2590(struct UnkStruct_020f2590 *this)
{
    func_020f45c4(this);
    this->unk_00 = &data_0213ef4c;
    this->unk_04 = 0x63;
    return this;
}
