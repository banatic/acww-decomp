/* func_02097b24 @ 0x02097b24, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02097ff0(void *addr, int flag);
extern int func_020978bc(void *base, int count);
extern int func_02065ec0(void *ptr);
extern int func_02097958(void *ptr);
extern void func_02066650(void *ptr);
extern int func_02097a74(void *ptr, int arg1, int arg2);
extern int func_02097900(void *ptr);
extern void func_02097a44(void *ptr);

extern unsigned char data_021f20fc[];

int func_02097b24(void)
{
    void *base;
    int count;
    int i;
    int local1 = 0;
    int local2 = 0;

    base = func_02097ff0((void *) data_021f20fc, 0);
    count = func_020978bc(base, 0xa);

    for (i = 0; i < count; i++) {
        void *ptr = (char *) base + (i << 8);
        if (func_02065ec0(ptr) != 0) {
            int val = func_02097958(ptr);
            if (val == -2) {
                func_02066650(ptr);
            } else {
                if (val == ~local2) {
                    goto then_block;
                }
                // else block
                if (func_02097a74(ptr, val, local1) != 0) {
                    func_02066650(ptr);
                }
                goto end_block;
            then_block:
                // then block
                if (func_02097900(ptr) < 0) {
                    func_02066650(ptr);
                } else {
                    func_02097a44(ptr);
                    func_02066650(ptr);
                }
            end_block:;
            }
        }
    }

    return func_020978bc(base, 0xa);
}
