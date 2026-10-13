/* func_ov109_0229d7b4 @ 0x0229d7b4, 0x12c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d7b4 {};
typedef void (UnkStruct_0229d7b4::*PMF)();
extern PMF data_ov109_0229db98;
extern PMF data_ov109_0229db90;
extern PMF data_ov109_0229db48;
extern PMF data_ov109_0229db80;
extern PMF data_ov109_0229db78;
extern PMF data_ov109_0229db70;
extern PMF data_ov109_0229db68;
extern PMF data_ov109_0229db60;
extern PMF data_ov109_0229db58;
extern PMF data_ov109_0229db50;
extern PMF data_ov109_0229db40;
extern PMF data_ov109_0229db88;
extern PMF data_ov109_0229db38;
extern PMF data_ov109_0229db30;
extern PMF data_ov109_0229db28;
extern PMF data_ov109_0229dba0;

extern "C" void func_ov109_0229d7b4(UnkStruct_0229d7b4 *obj)
{
    static int flag;
    static PMF table[16];
    if (!(flag & 1)) {
        table[0] = data_ov109_0229db98;
        table[1] = data_ov109_0229db90;
        table[2] = data_ov109_0229db48;
        table[3] = data_ov109_0229db80;
        table[4] = data_ov109_0229db78;
        table[5] = data_ov109_0229db70;
        table[6] = data_ov109_0229db68;
        table[7] = data_ov109_0229db60;
        table[8] = data_ov109_0229db58;
        table[9] = data_ov109_0229db50;
        table[10] = data_ov109_0229db40;
        table[11] = data_ov109_0229db88;
        table[12] = data_ov109_0229db38;
        table[13] = data_ov109_0229db30;
        table[14] = data_ov109_0229db28;
        table[15] = data_ov109_0229dba0;
        flag |= 1;
    }
    unsigned char idx = ((unsigned char *) obj)[0x8d];
    (obj->*(table[idx]))();
}
