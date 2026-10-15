/* func_ov054_02262134 @ 0x02262134, 0x54 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov054_02260474(void *self);
extern int *func_02095794(int param);
extern int func_02019e00(char *ptr);
extern int func_02019de8(char *ptr);
extern void func_ov054_02262528(char *p, int param);

int func_ov054_02262134(char *p)
{
    volatile int local[4];
    int *data;

    func_ov054_02260474(p);
    data = func_02095794(4);
    local[0] = data[0];
    local[1] = data[1];
    local[2] = data[2];

    if (func_02019e00(p + 0x564) == 10) {
        if (func_02019de8(p + 0x564) != 0) {
            *(short *) ((char *) p + 0x812) = 24;
            func_ov054_02262528(p, 2);
        }
    }
    return 1;
}
