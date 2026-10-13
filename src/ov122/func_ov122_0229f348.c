/* func_ov122_0229f348 @ 0x0229f348, 0x40 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a720(void *addr, unsigned char byte);
extern void func_ov002_02208098(void *s, int val);
extern void RtcSendPxiCommand(unsigned short cmd);
extern const unsigned char data_ov122_022a2584[];
extern const unsigned short data_ov122_022a258c[];

void func_ov122_0229f348(void *this_, int index)
{
    func_ov002_0220a720(((char *) this_ + 0x4698), data_ov122_022a2584[index]);
    ((unsigned char *) this_)[0xb8] = (unsigned char) index;
    func_ov002_02208098(this_, 25);
    RtcSendPxiCommand(data_ov122_022a258c[index]);
}
