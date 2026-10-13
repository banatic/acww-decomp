/* func_02098930 @ 0x02098930, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x0a04];
} UnkStruct_02098930;
extern UnkStruct_02098930 data_021ef8ec[4];
extern int func_0209985c(int a, int b);
extern int func_02098050(UnkStruct_02098930 *ptr, int b);

int func_02098930(int a, int b)
{
    int idx = func_0209985c(a, b);
    if (idx >= 0 && idx < 4) {
        return func_02098050(&data_021ef8ec[idx], b);
    }
    return idx;
}
