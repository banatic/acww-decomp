/* func_02030c84 @ 0x02030c84, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    unsigned char pad[0x138 - 4];
} RecA;
typedef struct {
    unsigned char pad[0x128];
    int unk_128;
    unsigned char pad_12C[0x138 - 0x12c];
} RecB;
typedef unsigned char RecC[0x138];
typedef struct {
    unsigned char unk_00;
    unsigned char pad[0x138 - 1];
} RecE;
typedef struct {
    int unk_00;
    int w1;
} CellT;

extern RecA data_021c3310[];
extern RecA data_021c3314[];
extern RecC data_021c31ec[];
extern RecB data_021c31e8[];
extern RecE data_021c331c[];

int func_02030c84(int x, int y, int value, int idx)
{
    CellT *cell;
    int rows, cols, flag;
    unsigned char *colBase;
    unsigned char *gridBase;
    unsigned char *rowBase;
    CellT *c;

    if (x < 0) {
        goto fail;
    }
    if (y < 0) {
        goto fail;
    }
    if ((unsigned int) x >= (unsigned int) data_021c3310[idx].unk_00) {
        goto fail;
    }
    if ((unsigned int) y >= (unsigned int) data_021c3314[idx].unk_00) {
        goto fail;
    }

    cell = (CellT *) (data_021c31ec[idx] + y * 0x30 + x * 8);
    goto have_cell;

fail:
    cell = 0;

have_cell:
    if (cell != 0) {
        cell->unk_00 = value;
        cell->w1 = value + 0x100;

        rows = data_021c3314[idx].unk_00 - 1;
        colBase = (unsigned char *) &data_021c31e8[idx];
        gridBase = data_021c31ec[idx];

        for (; rows >= 0; rows--) {
            cols = *(int *) (colBase + 0x128) - 1;
            rowBase = gridBase + rows * 0x30;

            for (; cols >= 0; cols--) {
                int occupied;
                c = (CellT *) (rowBase + cols * 8);
                occupied = (c->unk_00 != 0) && (c->w1 != 0);
                if (occupied == 0) {
                    flag = 0;
                    goto store;
                }
            }
        }
        flag = 1;

    store:
        data_021c331c[idx].unk_00 = (unsigned char) flag;
        return 1;
    }

    return 0;
}
