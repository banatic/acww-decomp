/* func_02060844 @ 0x02060844, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02138c48(void *addr, int a, int b, void (*callback)());
extern void func_02055764();
extern void func_02055ce8();

struct UnkStruct_02060844 {
    char pad_00[0x24];
    char unk_24;
    char pad_25[0x1af];
    char unk_1D4;
};

void *func_02060844(struct UnkStruct_02060844 *self)
{
    func_02138c48(&self->unk_1D4, 9, 156, func_02055764);
    func_02138c48(&self->unk_24, 9, 20, func_02055ce8);
    return self;
}
