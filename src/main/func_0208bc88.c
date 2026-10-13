/* func_0208bc88 @ 0x0208bc88, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208c630(void *, int);
extern void RtcSendPxiCommand(int);

struct Func0208bc88_Struct {
    unsigned char pad_00[0x20];
    int unk_20;
    unsigned char pad_24[0x4];
    unsigned char unk_28[1];
};

void func_0208bc88(struct Func0208bc88_Struct *obj)
{
    obj->unk_20 = 5;
    func_0208c630(obj->unk_28, 0);
    RtcSendPxiCommand(0x4b);
}
