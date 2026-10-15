/* func_ov068_022739f4 @ 0x022739f4, 0x68 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022739f4 {
    unsigned int x, y, z;
};
struct UnkStruct_022739f4_2 {
    char pad_00[0x74a];
    unsigned char unk_74A;
};

extern int func_020984e8(void);
extern struct UnkStruct_022739f4 *func_02095794(int);
extern void func_0204f818(int *, int *, struct UnkStruct_022739f4 *);
extern int func_020960f8(int, int);
extern int func_0203e070(struct UnkStruct_022739f4_2 *, int);

int func_ov068_022739f4(struct UnkStruct_022739f4_2 *p)
{
    int a, b;
    struct UnkStruct_022739f4 s;
    struct UnkStruct_022739f4 *ps;

    if (p->unk_74A == 0) {
        return 0;
    }

    func_020984e8();
    ps = func_02095794(4);
    s.x = ps->x;
    s.y = ps->y;
    s.z = ps->z;

    a = 0;
    b = 0;
    func_0204f818(&a, &b, &s);

    if (func_020960f8(37, 4) != 0) {
        if (a == 9 && b == 13) {
            func_0203e070(p, 0);
        }
    }

    return 1;
}
