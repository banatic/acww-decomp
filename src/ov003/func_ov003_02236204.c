/* func_ov003_02236204 @ 0x02236204, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
    int id;
} UnkStruct_02236204;
extern UnkStruct_02236204 *data_ov003_02262b38[8];

UnkStruct_02236204 *func_ov003_02236204(int id)
{
    unsigned int i;
    for (i = 0; i < 8; i++) {
        UnkStruct_02236204 *o = data_ov003_02262b38[i];
        if (o != 0 && id == o->id) {
            return o;
        }
    }
    return 0;
}
