/* func_020087a0 @ 0x020087a0, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(int);
extern int func_02073908(unsigned int, unsigned int);
extern void func_02010d64(void *);
extern int func_0200f554(void *);
extern void func_020087e0(void *);
extern unsigned int data_020ccf94;

struct UnkStruct_020087a0 {
    unsigned char pad_00[0x800];
    unsigned int unk_800;
};

void func_020087a0(struct UnkStruct_020087a0 *self)
{
    func_02010f5c((int) self);
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_02010d64(self);
    } else {
        func_0200f554(self);
        func_02010d64(self);
    }
    func_020087e0(self);
}
