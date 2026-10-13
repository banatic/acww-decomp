/* func_02044958 @ 0x02044958, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204b3d0(int);
extern void func_02044a30(int, void *, int, int);
extern int func_020b65c4(void);
extern void func_0205f9d4(int, int, int, int, int);

struct TwoInts {
    int first;
    int second;
};

void func_02044958(int a, struct TwoInts *b, int c)
{
    if (func_0204b3d0(a)) {
        struct TwoInts L;
        L.first = b->first;
        L.second = b->second;
        func_02044a30(a, &L, 0, c);
        if (c == 0) {
            func_0205f9d4((signed char) b->first, (signed char) b->second, func_020b65c4(), 0xfff1, 0);
        }
    }
}
