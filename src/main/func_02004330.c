/* func_02004330 @ 0x02004330, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
} Vector;
extern int data_021c67a4;
extern Vector data_021c67b8;
extern void func_020f4fb8(void *obj, Vector *v);

void func_02004330(void *obj, Vector *src)
{
    Vector local;

    if (!src) {
        return;
    }
    if (!data_021c67a4) {
        return;
    }

    local = *src;
    local.x -= data_021c67b8.x;
    local.y -= data_021c67b8.y;
    local.z -= data_021c67b8.z;

    func_020f4fb8(obj, &local);
}
