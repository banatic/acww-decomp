/* func_020ae6fc @ 0x020ae6fc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ae6fc {
    int a;
    signed char b;
};
extern void func_020ae564(struct UnkStruct_020ae6fc *);
extern void func_0209f100(void *, int);
extern unsigned char data_021dc7a8[];

void func_020ae6fc(struct UnkStruct_020ae6fc *p)
{
    p->a = 0;
    p->b = -1;
    func_020ae564(p);
    func_0209f100(data_021dc7a8, 8);
}
