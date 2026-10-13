/* func_02042a5c @ 0x02042a5c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02044858(int);
typedef struct {
    unsigned char a;
    unsigned char b;
    unsigned short c;
} Entry;
extern Entry data_021c7788[];

int func_02042a5c(Entry *out, int key)
{
    int ret = 0;
    int i;
    Entry *e;
    volatile unsigned short tmp;

    i = func_02044858(key);
    e = &data_021c7788[i];
    if (e->a) {
        out->a = e->a;
        tmp = e->c;
        out->c = tmp;
        out->b = e->b;
        e->a = 0;
        ret = 1;
    }
    return ret;
}
