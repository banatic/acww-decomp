/* func_0204a150 @ 0x0204a150, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0204a150 {
    unsigned short x;
};

extern int func_0204b8d4(struct UnkStruct_0204a150 *);
extern int func_0204b910(struct UnkStruct_0204a150 *);
extern void func_0204a25c(int, int, int, unsigned short, int);

void func_0204a150(int a, struct UnkStruct_0204a150 *b, int c, int d)
{
    unsigned short x = b->x;
    if (func_0204b8d4(b) != 0) {
        x = x - 3;
    } else if (func_0204b910(b) == 0) {
        x = x + 1;
    }
    func_0204a25c(a, c, d, x, 0);
}
