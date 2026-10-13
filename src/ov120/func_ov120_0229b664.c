/* func_ov120_0229b664 @ 0x0229b664, 0x54 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O1,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021fbddc;
extern void func_ov120_0229bfe8(void *obj);

extern struct {
    unsigned short unk0;
    unsigned short unk2;
} data_021fbe40;

void func_ov120_0229b664(void *obj)
{
    unsigned short flags = data_021fbe40.unk2;
    int c = 1;
    if (flags & 1) {
        goto call;
    }
    if (flags & 0x400) {
        goto call;
    }
    if (flags & 2) {
        goto call;
    }
    if (data_021fbdd8 == 0 || data_021fbddc == 0) {
        c = 0;
    }
    if (c) {
        goto call;
    }
    return;
call:
    func_ov120_0229bfe8(obj);
}
