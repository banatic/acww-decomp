/* func_ov068_02276230 @ 0x02276230, 0x22 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02276254(void);
extern int func_020984e8(void);
extern int func_02099640(int argument0);
extern void func_0209bb90(int, int);

void func_ov068_02276230(void *receiver)
{
    if (func_ov068_02276254() != 0) {
        return;
    }

    func_0209bb90(func_02099640((int) func_020984e8()) + 0xb4, 2);
}
