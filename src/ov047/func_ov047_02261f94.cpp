/* func_ov047_02261f94 @ 0x02261f94, 0x80 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261f94;

typedef void (UnkStruct_02261f94::*PMF)();

extern PMF data_ov047_02262b38, data_ov047_02262b40, data_ov047_02262b48, data_ov047_02262b50, data_ov047_02262b58;

extern "C" void func_ov047_02261f94(UnkStruct_02261f94 *p0, PMF *p1, int p2)
{
    static unsigned int s_flag = 0;
    static PMF s_table[5];

    unsigned int flg = s_flag;
    if ((flg & 1) == 0) {
        s_table[0] = data_ov047_02262b58;
        s_table[1] = data_ov047_02262b50;
        s_table[2] = data_ov047_02262b48;
        s_table[3] = data_ov047_02262b40;
        s_table[4] = data_ov047_02262b38;
        s_flag = flg | 1;
    }

    *p1 = s_table[p2];
}
