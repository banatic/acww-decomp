/* func_02082854 @ 0x02082854, 0x6a bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

typedef struct UnkStruct_02082854 {
    unsigned short v;
} UnkStruct_02082854;

extern int func_0204bcdc(UnkStruct_02082854 *);
extern int func_0204bc64(UnkStruct_02082854 *);

int func_02082854(void *self, UnkStruct_02082854 *other)
{
    int result;
    UnkStruct_02082854 *e;
    unsigned int ok1;
    unsigned int ok2;
    unsigned int t;
    int i;
    int off;
    unsigned int a;
    i = 0;
    result = -1;
    ok1 = 0;
    ok2 = 0;
    for (; i < 4; i++) {
        off = i * 8;
        e = (UnkStruct_02082854 *) ((char *) self + 0x44 + off);
        if (func_0204bcdc(e) != 0) {
            if (func_0204bc64(e) == func_0204bc64(other)) {
                t = 1;
            } else {
                t = ok1;
            }
        } else {
            a = ((UnkStruct_02082854 *) ((char *) self + off + 0x44))->v;
            if (a == other->v) {
                t = 1;
            } else {
                t = ok2;
            }
        }
        if (t > 0) {
            result = i;
            break;
        }
    }
    return result;
}
