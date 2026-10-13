/* func_ov068_0226caac @ 0x0226caac, 0x54 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0226caac {
    int halfExtentX;
    int halfExtentY;
    int top;
    int bottom;
};
struct UnkStruct_0226caac_2 {
    int x;
    int pad_04;
    int y;
};
struct UnkStruct_0226caac_3 {
    int x;
    int pad_04;
    int y;
};

int func_ov068_0226caac(struct UnkStruct_0226caac *s, struct UnkStruct_0226caac_2 *a, struct UnkStruct_0226caac_3 *b)
{
    int result = 0;
    int flag2 = 0;
    int flag1 = result;

    if (b->x > a->x - s->halfExtentX && b->x < a->x + s->halfExtentY) {
        flag1 = 1;
    }
    if (flag1) {
        if (b->y > a->y - s->top) {
            flag2 = 1;
        }
    }
    if (flag2) {
        if (b->y < a->y + s->bottom) {
            result = 1;
        }
    }
    return result;
}
