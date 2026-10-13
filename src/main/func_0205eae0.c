/* func_0205eae0 @ 0x0205eae0, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern u8 data_021ca16c[];

extern void func_0205f1bc(u8 *, int, int, int, int);
extern void func_0205f15c(u8 *, int, int, int);
extern void func_0206026c(u8 *, int);

void func_0205eae0(u8 *a, int b, int c, int d)
{
    func_0205f1bc(data_021ca16c, a[0], b, c, d);
    switch (b) {
        case 0x13:
            func_0206026c(a + 0x28, 1);
            break;
        case 0x15:
            func_0206026c(a + 0x28, 3);
            break;
        case 0x16:
            func_0206026c(a + 0x28, 2);
            break;
        case 0x18:
            func_0206026c(a + 0x28, 6);
            break;
        case 0x19:
        case 0x1b:
            func_0206026c(a + 0x28, 7);
            break;
        case 0x1a:
            func_0206026c(a + 0x28, 8);
            break;
        case 0x28:
            func_0205f15c(data_021ca16c, a[0], 1, d);
            break;
    }
}
