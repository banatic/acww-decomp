/* func_02027cc8 @ 0x02027cc8, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202d9c4(void *p);
extern int func_0209bc40(int v);
extern unsigned short func_02027d38(unsigned short *, int);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern int func_02015828(void *p, int val);
extern void func_020157c8(void *p, int a, int b);
struct DWord {
    unsigned int low;
    unsigned int high;
};
extern void func_0202dbf0(void *p, struct DWord data);
extern const struct DWord data_020d8dc8;
extern const struct DWord data_020d8e08;

#define Predicate_02027d38 ((int (*)(unsigned short *, int)) func_02027d38)

void func_02027cc8(void *arg)
{
    int id = func_0209bc40(func_0202d9c4(arg));
    switch (id) {
        case 0x0a:
            func_020157d4(arg, Predicate_02027d38, 13, 0);
            func_02015828(arg, 0);
            func_0202dbf0(arg, data_020d8dc8);
            break;
        case 0x13:
            func_020157c8(arg, 0x28, 1);
            func_02015828(arg, 2);
            func_0202dbf0(arg, data_020d8e08);
            break;
        default:
            func_02015828(arg, 7);
            break;
    }
}
