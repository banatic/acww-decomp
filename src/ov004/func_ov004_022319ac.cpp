/* func_ov004_022319ac @ 0x022319ac, 0xfc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct Pair {
    int x, y;
};
extern "C" {
// Preserve the guard reread after initializing the adjacent pair table.
extern volatile unsigned int data_ov004_022589c8;
extern Pair data_ov004_022589cc[], data_ov004_022589d4, data_ov004_022589dc, data_ov004_022589e4;
extern void *data_021c80bc;
extern void *func_0209847c(int);
extern unsigned short *func_020996c8(void *);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern void func_0204bc28(unsigned short *, int);
extern int func_02053bc0(unsigned short *);
extern void func_0204f538(void *, unsigned short *, int, int, int);
}
static inline bool is_empty(unsigned short *p)
{
    if (func_0204bcdc(p)) {
        unsigned short empty = 0xfff1;
        return func_0204bc64(p) == func_0204bc64(&empty);
    } else {
        return *p == 0xfff1;
    }
}
extern "C" void func_ov004_022319ac(void)
{
    if (!(data_ov004_022589c8 & 1)) {
        data_ov004_022589cc[0].x = 6;
        data_ov004_022589cc[0].y = 9;
        data_ov004_022589d4.x = 9;
        data_ov004_022589d4.y = 9;
        data_ov004_022589dc.x = 6;
        data_ov004_022589dc.y = 12;
        data_ov004_022589e4.x = 9;
        data_ov004_022589e4.y = 12;
        data_ov004_022589c8 |= 1;
    }
    void *room = data_021c80bc;
    if (room) {
        for (int i = 0; i < 4; ++i) {
            void *owner = func_0209847c(i);
            if (owner) {
                int x = data_ov004_022589cc[i & 3].x;
                int y = data_ov004_022589cc[i & 3].y;
                unsigned short item = *func_020996c8(owner);
                if (!is_empty(&item)) {
                    func_0204bc28(&item, 3);
                    if (x < 8 && func_02053bc0(&item) == 2) {
                        --x;
                    }
                    func_0204f538(room, &item, x, y, 0);
                }
            }
        }
    }
}
