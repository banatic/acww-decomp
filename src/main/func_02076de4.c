/* func_02076de4 @ 0x02076de4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern unsigned char data_ov003_0226053c;
extern struct UnkStruct_02076de4 *data_020ccf94;
void func_020736bc(struct UnkStruct_02076de4 *p, void *local, int a);
void func_ov003_0222e750(int _x);

struct UnkStruct_02076de4 {
    unsigned char pad_00[0x64];
    int unk_64;
};

void func_02076de4(int a)
{
    struct UnkStruct_02076de4 *p;
    unsigned char local;
    unsigned int hi;
    unsigned int cond;

    cond = (data_020e54a8 == 0) ? 1 : 0;
    if (cond != 0) {
        p = data_020ccf94;
        func_020736bc(p, &local, a);

        hi = ((unsigned int) local << 20) >> 24;

        local = (local & 0xF) | 0x10;

        if (local == 1) {
            data_ov003_0226053c = 1;
        } else {
            if (hi - 1 == p->unk_64) {
                data_ov003_0226053c = 0;
                func_ov003_0222e750(local);
            } else {
                data_ov003_0226053c = 1;
            }
        }
    }
}