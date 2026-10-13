/* func_02049d04 @ 0x02049d04, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef struct UnkStruct_02049d04 {
    int weight;
    u16 value;
} UnkStruct_02049d04;

typedef struct ListEntry {
    int count;
    UnkStruct_02049d04 *items;
} ListEntry;

extern int func_020644cc(int);
extern int func_02049ec4(int);
extern int func_02049d78(int);
extern ListEntry *data_020db7c4[][10];

int func_02049d04(int a, int b)
{
    int row;
    int total;
    int result;
    int min;
    int v0, v1, max;

    total = func_020644cc(0x64);
    result = 0xfff1;
    row = func_02049ec4(a);
    v0 = func_02049d78(a);
    min = v0;
    v1 = func_02049d78(b);
    max = v1;
    if (v0 > v1) {
        min = v1;
        max = v0;
    }
    {
        int off = max * 8;
        int count;
        ListEntry *le = data_020db7c4[row][min];
        UnkStruct_02049d04 *item = le[max].items;
        if (item != 0) {
            count = le[max].count;
            while (count != 0) {
                total -= item->weight;
                if (total <= 0) {
                    result = item->value;
                    break;
                }
                item++;
                count--;
            }
        }
    }
    return result;
}
