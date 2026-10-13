/* func_ov095_0229ae5c @ 0x0229ae5c, 0x28 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern int func_02088d9c(void *ptr);

typedef struct {
    int a;
    int b;
} Elem;

typedef struct {
    char pad_00[0x44];
    Elem *arr;
} UnkStruct_0229ae5c;

int func_ov095_0229ae5c(UnkStruct_0229ae5c *p, int key)
{
    if (key == 0xF8) {
        goto common;
    }
    if (key == 0xF9) {
        goto common;
    }
    if (key != 0xFA) {
        goto not_common;
    }
common:
    return func_02088d9c(&p->arr[key - 0xF8]) + 0x88;
not_common:
    return 0x80;
}
