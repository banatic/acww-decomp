/* func_0208fbf0 @ 0x0208fbf0, 0x10 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef int (*vfunc_t)(void *);

struct VTable {
    vfunc_t vfuncs[4];
};

int func_0208fbf0(void *obj)
{
    struct VTable *vt;
    vt = *(struct VTable **) obj;
    return vt->vfuncs[3](obj);
}
