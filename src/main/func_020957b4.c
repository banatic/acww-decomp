/* func_020957b4 @ 0x020957b4, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020d1894[];
extern struct __obj *func_02096718(int);
extern int func_02008258(struct __obj *obj, int field);
extern int func_0200c0dc(struct __obj *obj, unsigned char c1, unsigned char c2, int n, int arg);

struct __obj {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0x8];
    int unk_7FC;
};

int func_020957b4(unsigned char *p)
{
    struct __obj *obj;
    unsigned char c2;

    obj = func_02096718(4);
    c2 = data_020d1894[*p - 1];
    if (obj) {
        obj->unk_7FC = func_02008258(obj, obj->unk_7F0);
        return func_0200c0dc(obj, *p, c2, 5, -1);
    } else {
        return 0;
    }
}
