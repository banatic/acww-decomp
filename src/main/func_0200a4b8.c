/* func_0200a4b8 @ 0x0200a4b8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern void func_02010f5c(void *p);
extern void func_02010d64(void *p);
extern void func_0200a528(void *p);
extern void func_0200ae7c(void *p, unsigned char *ptr, unsigned char byte);
extern void func_0200f530(void *p, unsigned int *arr);
extern void func_0200ae04(void *p);
extern int func_02073908(unsigned int a, unsigned int b);
struct UnkStruct_0200a4b8_2 {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned char d;
};
struct UnkStruct_0200a4b8 {
    char pad_00[0x7d4];
    struct UnkStruct_0200a4b8_2 sub;
    char pad_7D8[0x28];
    unsigned int flags;
};

void func_0200a4b8(struct UnkStruct_0200a4b8 *p)
{
    struct UnkStruct_0200a4b8_2 *sub;
    unsigned int pos[2];
    unsigned char d;

    func_02010f5c(p);
    if (func_02073908(data_020ccf94, p->flags)) {
        func_02010d64(p);
        func_0200a528(p);
        sub = &p->sub;
        func_0200ae7c(p, &sub->b, sub->a);
    } else {
        sub = &p->sub;
        d = sub->d;
        pos[0] = sub->c;
        pos[1] = d;
        func_0200f530(p, pos);
        func_02010d64(p);
        func_0200a528(p);
        func_0200ae04(p);
    }
}
