/* func_02063e54 @ 0x02063e54, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02063e54 {
    int a;
    union {
        int b;
        unsigned char bytes[4];
    } u;
};

extern void func_0209e474(struct UnkStruct_02063e54 *);

unsigned char func_02063e54(void)
{
    struct UnkStruct_02063e54 s;
    s.a = 0;
    s.u.b = 0;
    func_0209e474(&s);
    return s.u.bytes[1];
}
