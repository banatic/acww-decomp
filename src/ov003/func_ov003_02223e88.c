/* func_ov003_02223e88 @ 0x02223e88, 0x1e bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    char pad_04[0x1c];
} UnkStruct_02223e88;
void *func_ov003_02223e88(char *o)
{
    int i;
    for (i = 0; i < 2; i++) {
        if (((UnkStruct_02223e88 *) o)[i].unk_00 == 3) {
            *(int *) (o + 0x40) = i;
            return &((UnkStruct_02223e88 *) o)[i];
        }
    }
    return 0;
}
