/* func_02098930 @ 0x02098930, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0x0a04];
} UnkStruct_02098930;
extern UnkStruct_02098930 data_021ef8ec[4];
extern int func_0209985c(int);
extern void func_02098050(UnkStruct_02098930 *ptr, unsigned int value);

void func_02098930(int a, int b)
{
    int idx = func_0209985c(a);
    if (idx >= 0 && idx < 4) {
        func_02098050(&data_021ef8ec[idx], b);
    }
}
