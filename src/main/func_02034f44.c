/* func_02034f44 @ 0x02034f44, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x12];
    unsigned char flag;
    unsigned char pad_13[0x9];
} Elem;

typedef struct {
    Elem arr[16];
    int count;
} UnkStruct_02034f44;

int func_02034f44(UnkStruct_02034f44 *p)
{
    int result = -1;
    int i;
    for (i = 0; i < p->count; i++) {
        if (p->arr[i].flag != 0) {
            result = i;
            break;
        }
    }
    return result;
}
