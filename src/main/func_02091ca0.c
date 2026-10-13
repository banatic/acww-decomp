/* func_02091ca0 @ 0x02091ca0, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e2b44[];
extern char data_021d52d8[];
extern void func_02094bcc(void *a, void *b, int c);

struct UnkStruct_02091ca0 {
    unsigned char v[4];
};

void func_02091ca0(void *p)
{
    unsigned char buf[4];
    unsigned char *src;
    unsigned char *dst;
    int count;
    short s;
    void *dest;

    *(struct UnkStruct_02091ca0 *) buf = *(struct UnkStruct_02091ca0 *) ((unsigned char *) p + 4);

    s = *(short *) (data_021d52d8 + 0x1c * buf[0] + 0x10);
    dest = data_020e2b44 + 12 * s;
    func_02094bcc(p, dest, 0);
}