/* func_02096d78 @ 0x02096d78, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

extern int func_0204e414(void);
extern void *func_0204f5e0(int, int, int, int, int, int);

int func_02096d78(void)
{
    void *obj = (void *) func_0204e414();
    int i = 0;
    int a = i;
    int b = i;
    int c = i;

    while (i < *(int *) ((char *) obj + 0x10)) {
        int j = a;
        while (j < *(int *) ((char *) obj + 0xc)) {
            int qj = j >> 4;
            int qi = i >> 4;
            void *r = func_0204f5e0((int) obj, qj, qi, j - (qj << 4), i - (qi << 4), c);
            if (r != 0) {
                int flag = b;
                if (*(u16 *) r >= 0x1520 && *(u16 *) r <= 0x1520) {
                    flag = 1;
                }
                if (flag != 0) {
                    return 1;
                }
            }
            j++;
        }
        i++;
    }
    return 0;
}
