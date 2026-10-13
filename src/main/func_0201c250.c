/* func_0201c250 @ 0x0201c250, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0201c250 UnkStruct_0201c250;

typedef struct {
    char pad_00[0x78];
    int (*func)(UnkStruct_0201c250 *);
} VTable;

struct UnkStruct_0201c250 {
    VTable *vtable;
};

int func_0201c250(UnkStruct_0201c250 *this)
{
    int result = 2;
    int val;

    val = this->vtable->func(this);
    switch (val) {
        case 0:
            result = 0;
            break;
        case 1:
            result = 1;
            break;
        default:
            break;
    }
    return result;
}
