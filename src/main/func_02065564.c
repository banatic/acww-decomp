/* func_02065564 @ 0x02065564, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b6660(void);
extern int func_020b6640(void);
extern void RtcSendPxiCommand(int);
extern unsigned short data_020ccb6c[];
extern unsigned short data_020ccb68[];

struct UnkStruct_02065564 {
    int state;
    int count;
};

void func_02065564(struct UnkStruct_02065564 *p)
{
    if (p->state == 0) {
        p->count--;
        if (p->count < 0) {
            int arg;
            if (func_020b6660() != 0 || func_020b6640() != 0) {
                arg = data_020ccb6c[p->state];
            } else {
                arg = data_020ccb68[p->state];
            }
            RtcSendPxiCommand(arg);
            p->state = 2;
        }
    } else {
        p->state = 2;
    }
}
