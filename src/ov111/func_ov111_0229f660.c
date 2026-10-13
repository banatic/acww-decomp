/* func_ov111_0229f660 @ 0x0229f660, 0x48 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_02051c8c_unk(const void *, int);
extern void func_ov111_0229f854(unsigned char *);
extern void func_02095804(void);
extern int RtcSendPxiCommand(int);
extern void func_ov111_0229fc9c(unsigned char *);

int func_ov111_0229f660(unsigned char *self)
{
    if (self[0x9b]) {
        return 0;
    }
    if (func_02051c8c_unk(self + 0x3d16, 0x10) == 0) {
        func_ov111_0229f854(self);
    } else {
        func_02095804();
        RtcSendPxiCommand(0x32);
        func_ov111_0229fc9c(self);
        return 1;
    }
    return 0;
}
