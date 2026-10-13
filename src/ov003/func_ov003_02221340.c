/* func_ov003_02221340 @ 0x02221340, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02222860(void *);
typedef struct {
    char pad_00[4];
    int unk_04;
    char pad_08[8];
    int unk_10;
    int unk_14;
    char pad_18[0x88];
    unsigned char unk_A0;
    char pad_A1[3];
} Elem;
typedef struct {
    int x;
    int y;
} UnkStruct_02221340;
extern Elem data_ov003_0223cfe4[];
int func_ov003_02221340(int idx, UnkStruct_02221340 *key)
{
    int found;
    int i;
    UnkStruct_02221340 loc;
    UnkStruct_02221340 *q;
    Elem *e;
    found = 0;
    e = &data_ov003_0223cfe4[idx * 4];
    i = 0;
    for (; i < 4; i++) {
        if (e->unk_04 != 0) {
            loc.x = e->unk_10;
            q = &loc;
            loc.y = e->unk_14;
            if ((loc.x == key->x) && (q->y == key->y)) {
                if (e->unk_A0 != 0) {
                    found = 1;
                }
                func_ov003_02222860(e);
                break;
            }
        }
        e++;
    }

    return found;
}
