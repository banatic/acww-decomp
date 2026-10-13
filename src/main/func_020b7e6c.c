/* func_020b7e6c @ 0x020b7e6c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b7e9c(void *ptr, int arg);

struct func_020b7e6c_struct {
    unsigned char pad_00[0x1c];
    unsigned int unk_1C;
    unsigned int unk_20;
    unsigned int unk_24;
};

void func_020b7e6c(struct func_020b7e6c_struct *ptr)
{
    func_020b7e9c(ptr, 0);
    ptr->unk_1C = 0;
    ptr->unk_20 = 0;
    ptr->unk_24 = 0;
}
