/* func_020040bc @ 0x020040bc, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_020040bc;
extern int data_021c67a4;
extern UnkStruct_020040bc data_021c67b8;
extern int func_020f9ea4(void *self, UnkStruct_020040bc *v);
int func_020040bc(void *self, UnkStruct_020040bc *v)
{
    UnkStruct_020040bc t;
    if (v != 0) {
        if (data_021c67a4 == 0) {
            return -1;
        }
        t.x = v->x - data_021c67b8.x;
        t.y = v->y - data_021c67b8.y;
        t.z = v->z - data_021c67b8.z;
        return func_020f9ea4(self, &t);
    }
    return -1;
}
