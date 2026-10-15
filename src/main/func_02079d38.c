/* func_02079d38 @ 0x02079d38, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 data[0x7ec];
} BigStruct;

typedef struct {
    u8 data[0x2c];
} SmallStruct;

extern SmallStruct *func_02079350(void);
extern int func_0208150c(BigStruct *b);
extern int func_02003704(int x);
extern int func_0207a210(unsigned int a, int i);
extern void func_020794d4(SmallStruct *p, int x);
extern void func_02079540(SmallStruct *p, int x);

void func_02079d38(unsigned int a, BigStruct *b)
{
    SmallStruct *p = func_02079350();
    int i;
    int varB = 0;
    int varA = 0;

    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(b)) != 0) {
            if (func_0207a210(a, i) != -1) {
                func_020794d4(p, varA);
                func_02079540(p, 1);
            } else {
                func_020794d4(p, 1);
                func_02079540(p, varB);
            }
        } else {
            func_020794d4(p, 3);
            func_02079540(p, 7);
        }
        b++;
        p++;
    }
}
