/* func_ov073_0227942c @ 0x0227942c, 0x3a bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern void func_0201af58(void *dst, void *src, int param2, int param3);
extern int func_0201ae8c(void *src);

typedef struct {
    char pad_00[0x5c];
    int inner;
    char pad_60[0x34];
    short value;
} UnkStruct_0227942c;

typedef struct {
    int x;
    int y;
    int z;
} UnkStruct_0227942c_2;

int func_ov073_0227942c(UnkStruct_0227942c *self, UnkStruct_0227942c_2 *out, int param2)
{
    int buf[3];
    int result = 0;

    func_0201af58(buf, &self->inner, param2, self->value);
    if (func_0201ae8c(buf) != 1) {
        out->x = buf[0];
        out->y = buf[1];
        out->z = buf[2];
        result = 1;
    }
    return result;
}
