/* func_ov126_022a11d8 @ 0x022a11d8, 0x50 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char data_021f6c58;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov126_022a0854(void *, unsigned char);
extern void func_ov126_022a0680(void *);
extern void func_ov126_022a0168(void *);
extern void RtcSendPxiCommand(int);

typedef struct {
    char pad_00[0xA8];
    unsigned char unk_A8;
} UnkStruct_022a11d8;

void func_ov126_022a11d8(UnkStruct_022a11d8 *s)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (s), 0);
        return;
    }
    {
        unsigned char old = s->unk_A8;
        func_ov126_022a0854(s, data_021f6c58);
        if (old == s->unk_A8) {
            return;
        }
        func_ov126_022a0680(s);
        func_ov126_022a0168(s);
        RtcSendPxiCommand(0x15);
    }
}
