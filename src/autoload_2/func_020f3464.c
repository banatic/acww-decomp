/* func_020f3464 @ 0x020f3464, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020f45c4(void *);
extern char data_0213eba4;

struct UnkStruct_020f3464 {
    void *unk_00;
    char unk_04;
};

struct UnkStruct_020f3464 *func_020f3464(struct UnkStruct_020f3464 *this)
{
    func_020f45c4(this);
    this->unk_00 = &data_0213eba4;
    this->unk_04 = 0x1f;
    return this;
}
