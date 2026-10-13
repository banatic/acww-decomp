/* func_02097300 @ 0x02097300, 0x7a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020972f0(int);
extern int func_020972e4(int);
extern int func_0209727c(int, int);
extern int func_02097188(int, int, int, int);
extern int func_020644cc(int);

struct UnkStruct_02097300 {
    int unk_00;
    int unk_04;
};

int func_02097300(struct UnkStruct_02097300 *p)
{
    int a, b, c;
    int tmp, res;

    a = func_020972f0((unsigned char) p->unk_04);
    b = func_020972e4((unsigned char) p->unk_04);
    c = func_0209727c(a, b);

    if (c == b) {
        return func_02097188(a, b, (unsigned char) p->unk_04, 0);
    } else {
        tmp = func_0209727c(0x22, 0x38) + c;
        res = func_020644cc(tmp);
        if (res < c) {
            return func_02097188(a, b, (unsigned char) p->unk_04, 0);
        } else {
            return func_02097188(0x22, 0x38, (unsigned char) p->unk_04, 1);
        }
    }
}
