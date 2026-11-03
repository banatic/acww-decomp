/* player_field_2416_2: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02088c10 @ 0x02088c10, 0x2 bytes, Thumb
 * func_02088c0c @ 0x02088c0c, 0x2 bytes, Thumb
 * func_02088c08 @ 0x02088c08, 0x2 bytes, Thumb
 * func_02088c04 @ 0x02088c04, 0x4 bytes, Thumb
 * func_02088be0 @ 0x02088be0, 0x22 bytes, Thumb
 */

struct UnkStruct_02088be0 {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char unk_05;
    unsigned char unk_06;
};

extern void func_0209df64(unsigned char *buf);

void func_02088c10(void *object) {}

void func_02088c0c(void *object) {}

void func_02088c08(void *object) {}

int func_02088c04(int p0)
{
    return ((int) (p0) + (4));
}

void func_02088be0(struct UnkStruct_02088be0 *param)
{
    unsigned char buf[3];
    func_0209df64(buf);
    param->unk_06 = buf[2];
    param->unk_05 = buf[1];
    param->unk_04 = buf[0];
}
