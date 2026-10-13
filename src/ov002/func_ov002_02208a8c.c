/* func_ov002_02208a8c @ 0x02208a8c, 0x44 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208a0c(void *ptr, int arg);
extern void RtcSendPxiCommand(int cmd);

int func_ov002_02208a8c(void *base, int index, int offset)
{
    unsigned char v;
    v = *(unsigned char *) ((char *) base + (offset + 5 * index) + 0x3cc);
    if (v != 0xe) {
        func_ov002_02208a0c(base, 4);
    }
    switch (v) {
        case 0xf:
            RtcSendPxiCommand(0x28);
            break;
        case 0xe:
            RtcSendPxiCommand(0x29);
            break;
        default:
            RtcSendPxiCommand(0x27);
            break;
    }
    return v;
}
