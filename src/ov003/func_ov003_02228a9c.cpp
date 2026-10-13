/* func_ov003_02228a9c @ 0x02228a9c, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O1,s
 */

struct UnkStruct_02228a9c;
typedef void (UnkStruct_02228a9c::*PMF)(void *, int);
struct Entry {
    PMF fn;
    int a;
    int b;
};
extern Entry data_ov003_0225f1d0[];

extern "C" void func_ov003_02228a9c(UnkStruct_02228a9c *self, int idx, char *obj, int q)
{
    int i;
    Entry *e;
    if (idx >= 0 && idx < 5) {
        *(int *) (obj + 0x80) = idx;
        i = *(int *) (obj + 0x80);
        e = &data_ov003_0225f1d0[i];
        if (e->fn) {
            (self->*(e->fn))(obj, q);
        }
    }
}
