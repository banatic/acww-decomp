/* func_0206dbc0 @ 0x0206dbc0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8a70(void *, int, int, int);

struct UnkStruct_0206dbc0 {
    unsigned char pad_00[0x6c];
    unsigned char flag;
};

void func_0206dbc0(struct UnkStruct_0206dbc0 *p, int b)
{
    func_020a8a70(p, b, 0, 0);
    p->flag = 1;
}
