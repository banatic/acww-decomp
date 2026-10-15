/* func_02093628 @ 0x02093628, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02094cf8(int, int, int, int, int, int);
extern int func_02094840(int, int, int, int, int, void (*)(void *));
extern void func_02093678(void *);
extern int data_020e2964;

int func_02093628(int p0, int p1, int p2, int p3)
{
    int result = 3;
    if (func_02094cf8(0x59, p0, p1, p2, p3, (int) &data_020e2964) < 3) {
        func_02094840(3, p0, p1, p2, p3, func_02093678);
        result = 1;
    }
    return result;
}
