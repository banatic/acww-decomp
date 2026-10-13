/* func_020f2720 @ 0x020f2720, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f45c4(void *);
extern char data_0213eee4[];

struct UnkStruct_020f2720 {
    void *vtable;
    char flag;
};

struct UnkStruct_020f2720 *func_020f2720(struct UnkStruct_020f2720 *this)
{
    func_020f45c4(this);
    this->vtable = data_0213eee4;
    this->flag = 0x34;
    return this;
}
