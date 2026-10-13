/* func_ov002_0220a4bc @ 0x0220a4bc, 0xc bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int RtcSendPxiCommand(int);

int func_ov002_0220a4bc(char *self)
{
    // DECLS
    // ENDDECLS
    return RtcSendPxiCommand(0x33);
}
