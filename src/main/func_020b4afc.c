/* func_020b4afc @ 0x020b4afc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b4afc {
    char pad_00[0x2c];
    void *unk_2C;
};

extern char *func_02137550(void *dest, unsigned int size);
extern int func_020a89f8(void *ptr, void *data);

void func_020b4afc(struct UnkStruct_020b4afc *s, int value)
{
    unsigned char buf[4];
    func_02137550(buf, 4);
    buf[0] = (unsigned char) value;
    buf[1] = (unsigned char) (value >> 8);
    func_020a89f8(s->unk_2C, buf);
}
