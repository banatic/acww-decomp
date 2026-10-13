/* func_ov003_02218688 @ 0x02218688, 0x28 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020779b8(void *, int, int);
extern void func_02077910(void *, short);

struct UnkStruct_02218688 {
    char pad_00[5];
    char data[2];
    char flag;
};

void func_ov003_02218688(struct UnkStruct_02218688 *self, char byte, int a, int b, short s)
{
    self->flag = byte;
    func_020779b8(self, a, b);
    func_02077910(self->data, s);
}
