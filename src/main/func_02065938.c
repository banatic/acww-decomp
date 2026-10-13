/* func_02065938 @ 0x02065938, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020658e8(void *p1, void *p2);
extern void func_02064ddc(void *p1, void *p2);
extern void func_020653fc(void *p1, void *p2);
extern char data_0213fee4;

struct Elem {
    char data[0x44];
};

struct Main {
    char pad_00[0x54];
    int count;
    struct Elem elems[1];
};

int func_02065938(struct Main *self)
{
    unsigned char buf[0x24];
    int i;
    struct Elem *p;

    func_020658e8(&data_0213fee4, buf);

    p = self->elems;
    for (i = 0; i < self->count; i++) {
        func_02064ddc(p, buf);
        p++;
    }

    func_020653fc((char *) self + 0x124, buf);

    return 1;
}
