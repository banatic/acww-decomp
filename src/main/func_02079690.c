/* func_02079690 @ 0x02079690, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char *unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
} Map;
extern Map *data_021c80bc;
extern int func_02037d80(unsigned char *cell, int k);
int func_02079690(int *p)
{
    Map *m = data_021c80bc;
    if (m != 0) {
        unsigned char *cell;
        unsigned int y = (unsigned int) (p[2] >> 17);
        unsigned int x = (unsigned int) (p[0] >> 17);
        if (x < m->unk_04 && y < m->unk_08 && m->unk_00 != 0) {
            cell = m->unk_00 + (x + y * m->unk_04) * 0x28;
        } else {
            cell = 0;
        }
        if (cell != 0 && func_02037d80(cell, 8) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
