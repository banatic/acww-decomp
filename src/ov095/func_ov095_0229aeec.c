/* func_ov095_0229aeec @ 0x0229aeec, 0x6c bytes, Thumb, module ov095
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov095_0229e664;
extern char data_ov095_0229e68c;

typedef struct {
    unsigned char pad_00[0x19];
    unsigned char unk_19;
    unsigned char unk_1A;
} UnkStruct_0229aeec;

void func_02088df8(int, const void *, int, int, int, int, int, int, int, int, int, int);

void func_ov095_0229aeec(UnkStruct_0229aeec *p1, int p2, int p3)
{
    func_02088df8(1, &data_ov095_0229e664, p2, p3, p1->unk_19, 2, 0x1000, 0x1000, 0, -1, 0, 0);
    func_02088df8(1, &data_ov095_0229e68c, p2, p3, p1->unk_1A, 2, 0x1000, 0x1000, 0, -1, 0, 0);
}
