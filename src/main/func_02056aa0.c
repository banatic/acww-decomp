/* func_02056aa0 @ 0x02056aa0, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MTX_Identity33_(void *p);

typedef struct {
    int w[9];
} UnkStruct_02056aa0;

typedef struct {
    int unk_00;
    UnkStruct_02056aa0 data;
    int extra[3];
} UnkStruct_02056aa0_2;

typedef struct {
    char pad_00[0x28];
    UnkStruct_02056aa0 data;
    int extra[3];
} UnkStruct_02056aa0_3;

typedef struct {
    char pad_00[0x34];
    UnkStruct_02056aa0_3 *base;
} UnkStruct_02056aa0_4;

typedef struct {
    const unsigned char *str;
    UnkStruct_02056aa0_4 *inner;
} Param;

void func_02056aa0(UnkStruct_02056aa0_2 *out, Param *param)
{
    UnkStruct_02056aa0_3 *item;

    item = &param->inner->base[param->str[1]];
    if (item->data.w[0] == 0 && item->data.w[1] == 0 && item->data.w[2] == 0 && item->data.w[3] == 0 && item->data.w[4] == 0 &&
        item->data.w[5] == 0 && item->data.w[6] == 0 && item->data.w[7] == 0 && item->data.w[8] == 0) {
        MTX_Identity33_(&out->data);
    } else {
        out->data = item->data;
    }
    out->extra[0] = item->extra[0];
    out->extra[1] = item->extra[1];
    out->extra[2] = item->extra[2];
}
