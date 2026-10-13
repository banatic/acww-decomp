/* func_020a8f50 @ 0x020a8f50, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02050d6c(void *);
extern char data_020e3dac;

struct UnkStruct_020a8f50 {
    void *unk_00;        // offset 0x00
    char pad_04[0x78];   // offset 0x04, ends at 0x7c
    unsigned int unk_7C; // offset 0x7c
    unsigned int unk_80; // offset 0x80
};

struct UnkStruct_020a8f50 *func_020a8f50(struct UnkStruct_020a8f50 *this)
{
    func_02050d6c(this);
    this->unk_00 = &data_020e3dac;
    this->unk_7C = 0;
    this->unk_80 = 0;
    return this;
}
