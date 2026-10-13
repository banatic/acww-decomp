/* func_0203c3ec @ 0x0203c3ec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern short func_0203f768(void *);

struct func_0203c3ec_obj {
    char pad_00[0x194];
    char data[0x18];
    short result;
};

void func_0203c3ec(struct func_0203c3ec_obj *s)
{
    s->result = func_0203f768(&s->data);
}
