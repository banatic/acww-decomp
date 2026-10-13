/* func_020851e0 @ 0x020851e0, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_020738bc(void *ptr, int value);

struct UnkStruct_020851e0 {
    unsigned short unk_00;
};

int func_020851e0(struct UnkStruct_020851e0 *s)
{
    unsigned masked = (unsigned) (s->unk_00 & 0xfff);
    if (masked < 0x26) {
        return func_020738bc(data_020ccf94, masked + 0x20);
    } else {
        return 0;
    }
}
