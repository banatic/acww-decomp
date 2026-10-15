/* func_ov119_0229ac3c @ 0x0229ac3c, 0x42 bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov119_0229ae50(void *receiver);
extern int func_02077c3c(int);
extern int func_02077e50(void *friend_data);
extern int func_02077e74(int, int);

int func_ov119_0229ac3c(int r1, int r6)
{
    int r5;
    int r4;
    int r0;

    r5 = (int) func_ov119_0229ae50((void *) r1);
    r4 = 0;
    while (r4 < 0x20) {
        r0 = func_02077c3c(r5);
        if (func_02077e50((void *) r0) != 0) {
            r0 = func_02077c3c(r5);
            if (func_02077e74(r6, r0) != 0) {
                return 1;
            }
        }
        r5 += 0x24;
        r4++;
    }
    return 0;
}
