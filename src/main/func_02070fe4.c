/* func_02070fe4 @ 0x02070fe4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020712b0(void *self, int p2);
extern int func_020712ec(void *self, int p2);
extern char data_021dc7bc;
extern int func_02098844(void *addr, int val);
extern int func_02099870(int object);
extern int func_02095074(int a, int b);

int func_02070fe4(void *self, int p1, int p2)
{
    int forwarded_value;

    int masked;
    if ((unsigned int) func_020712b0(self, p2) > 1) {
        goto fail;
    }
    masked = (func_020712ec(self, p2) - 1) & 3;
    if ((forwarded_value = (int) func_02098844(&data_021dc7bc, masked)) == 0) {
        goto fail;
    }
    func_02095074(func_02099870((int) forwarded_value), p1);
    return 1;
fail:
    return 0;
}
