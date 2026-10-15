/* func_ov002_0220a4bc @ 0x0220a4bc, 0xc bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void RtcSendPxiCommand(int);

void func_ov002_0220a4bc(void *receiver)
{
    // DECLS
    // ENDDECLS
    RtcSendPxiCommand(0x33);
}
