/* func_02039628 @ 0x02039628, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2e4];
    int array[4];
} UnkStruct_02039628;

extern int func_02039474(UnkStruct_02039628 *s, int val);

int func_02039628(UnkStruct_02039628 *s, int val)
{
    int result = 0;
    if (func_02039474(s, val)) {
        result = 1;
    } else {
        int i;
        for (i = 0; i < 4; i++) {
            if (s->array[i] == 0) {
                s->array[i] = val;
                result = 1;
                break;
            }
        }
    }
    return result;
}
