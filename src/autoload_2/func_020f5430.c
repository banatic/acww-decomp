/* func_020f5430 @ 0x020f5430, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f560c(void *);
extern int data_0213f058;

struct UnkStruct_020f5430 {
    int *unk_00;
    char pad_04[0x3a];
    unsigned char unk_3E;
};

void *func_020f5430(struct UnkStruct_020f5430 *this)
{
    func_020f560c(this);
    this->unk_00 = &data_0213f058;
    this->unk_3E = 0x63;
    return this;
}
