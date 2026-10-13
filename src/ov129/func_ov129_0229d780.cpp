/* func_ov129_0229d780 @ 0x0229d780, 0x120 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229d780 {
  public:
    char pad_00[0x8d];
    unsigned char idx;
};

typedef void (UnkStruct_0229d780::*PMF)();

extern const PMF data_ov129_0229db68;
extern const PMF data_ov129_0229dbd8;
extern const PMF data_ov129_0229db60;
extern const PMF data_ov129_0229dbc8;
extern const PMF data_ov129_0229db58;
extern const PMF data_ov129_0229db70;
extern const PMF data_ov129_0229db78;
extern const PMF data_ov129_0229dba8;
extern const PMF data_ov129_0229db80;
extern const PMF data_ov129_0229db88;
extern const PMF data_ov129_0229dbb0;
extern const PMF data_ov129_0229dbb8;
extern const PMF data_ov129_0229dbd0;
extern const PMF data_ov129_0229dbe0;
extern const PMF data_ov129_0229dbf0;

extern "C" void func_ov129_0229d780(UnkStruct_0229d780 *obj)
{
    static int flag = 0;
    static PMF arr[15];
    if (!(flag & 1)) {
        arr[0] = data_ov129_0229db68;
        arr[1] = data_ov129_0229dbd8;
        arr[2] = data_ov129_0229db60;
        arr[3] = data_ov129_0229dbc8;
        arr[4] = data_ov129_0229db58;
        arr[5] = data_ov129_0229db70;
        arr[6] = data_ov129_0229db78;
        arr[7] = data_ov129_0229dba8;
        arr[8] = data_ov129_0229db80;
        arr[9] = data_ov129_0229db88;
        arr[10] = data_ov129_0229dbb0;
        arr[11] = data_ov129_0229dbb8;
        arr[12] = data_ov129_0229dbd0;
        arr[13] = data_ov129_0229dbe0;
        arr[14] = data_ov129_0229dbf0;
        flag |= 1;
    }
    (obj->*arr[obj->idx])();
}
