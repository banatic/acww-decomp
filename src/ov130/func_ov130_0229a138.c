/* func_ov130_0229a138 @ 0x0229a138, 0x10 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char unk_00[5];
    unsigned char idx;
} UnkStruct_0229a138;
extern unsigned int data_ov130_0229a940[];
void *func_ov130_0229a138(UnkStruct_0229a138 *obj)
{
    return (void *) data_ov130_0229a940[obj->idx];
}
