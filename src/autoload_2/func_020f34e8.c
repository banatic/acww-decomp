/* func_020f34e8 @ 0x020f34e8, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f34e8 {
    void *unk_00;
};

extern char data_0213eb70;
extern void func_020f4514(void *);
extern void func_020edb3c(void *);

void *func_020f34e8(struct UnkStruct_020f34e8 *this)
{
    this->unk_00 = (void *) &data_0213eb70;
    func_020f4514(this);
    func_020edb3c(this);
    return this;
}
