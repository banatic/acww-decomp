/* func_ov068_0226d20c @ 0x0226d20c, 0x58 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} UnkStruct_0226d20c;
typedef struct {
    char pad_00[0x5c];
    UnkStruct_0226d20c pos;
} UnkStruct_0226d20c_2;

extern int func_0201cddc(void *argument0);
extern UnkStruct_0226d20c_2 *func_02096190(int);
extern void *data_021c80bc;
extern int func_0204f61c(void *, int, int, int);

int func_ov068_0226d20c(void *argument0)
{
    volatile UnkStruct_0226d20c t;
    UnkStruct_0226d20c_2 *o;
    void *g;
    UnkStruct_0226d20c *v;
    unsigned char k;

    k = (unsigned char) (func_0201cddc(argument0) + 0xfd);
    if (k <= 1) {
        o = func_02096190(4);
        g = data_021c80bc;
        if (o != 0 && g != 0) {
            v = &o->pos;
            t.x = v->x;
            t.y = v->y;
            t.z = v->z;
            if (func_0204f61c(g, v->x >> 17, v->z >> 17, 0x200) == 0) {
                return 1;
            }
        }
    }
    return 0;
}
