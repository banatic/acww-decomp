/* func_ov073_02278d08 @ 0x02278d08, 0x58 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ea80(int, int);

typedef struct {
    char pad_00[0xb0];
    int state;
} UnkStruct_02278d08;

typedef struct {
    unsigned int word;
    unsigned char byte;
} UnkStruct_02278d08_2;

typedef struct {
    unsigned int word;
    unsigned char byte;
} TableEntry;

extern TableEntry data_ov073_02279844[];

void func_ov073_02278d08(UnkStruct_02278d08 *self, UnkStruct_02278d08_2 *out)
{
    if (self->state == 0) {
        if (func_0202ea80(3, 1) != 0) {
            self->state = 1;
        }
    }
    if (self->state >= 0 && self->state < 3) {
        out->byte = data_ov073_02279844[self->state].byte;
        out->word = data_ov073_02279844[self->state].word;
    }
}
