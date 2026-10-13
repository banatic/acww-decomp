/* func_0209e1ac @ 0x0209e1ac, 0x42 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Timer {
    unsigned int unk_00;
    unsigned char value;
} Timer;

extern void func_0209e1f0(Timer *timer, int param);

void func_0209e1ac(Timer *timer, int delta)
{
    int diff = timer->value - delta;
    if (diff < 1) {
        int r6;
        if (diff == 0) {
            diff = 12;
            r6 = 1;
        } else {
            if (diff < 0) {
                diff = -diff;
            }
            r6 = diff / 12 + 1;
            diff = 12 - diff % 12;
        }
        func_0209e1f0(timer, r6);
    }
    timer->value = diff;
}
