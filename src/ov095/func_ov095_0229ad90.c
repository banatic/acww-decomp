/* func_ov095_0229ad90 @ 0x0229ad90, 0x34 bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int word[2];
} Entry8;
extern Entry8 data_ov095_0229e814[];
extern int func_02088d9c(Entry8 *ptr);

int func_ov095_0229ad90(int unused, int id)
{
    if (id >= 0x10c && id <= 0x10f) {
        return func_02088d9c(&data_ov095_0229e814[id - 0x10c]) + 0x88;
    } else {
        return 0x80;
    }
}
