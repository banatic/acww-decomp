/* func_ov050_02264834 @ 0x02264834, 0x44 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02264834 {
  public:
    char pad_00[0x654];
    int member;
};
typedef int (UnkStruct_02264834::*PMF)();
struct PMFEntry {
    PMF pmf;
    int pad_08[2];
};
extern PMFEntry data_ov050_02265f08[];
extern "C" void func_ov050_02264834(UnkStruct_02264834 *obj, int n)
{
    int ret = 1;
    if (data_ov050_02265f08[n].pmf != 0) {
        ret = (obj->*data_ov050_02265f08[n].pmf)();
    }
    if (ret != 0) {
        obj->member = n;
    }
}
