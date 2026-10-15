/* func_ov131_0229b700 @ 0x0229b700, 0x94 bytes, Thumb, module ov131
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229b700;
typedef void (UnkStruct_0229b700::*PMF)();
class UnkStruct_0229b700 {
  public:
    char pad_00[0x8c];
    unsigned char selector;
};
extern "C" {
void func_ov131_0229b474(UnkStruct_0229b700 *);
void func_ov131_0229b43c(UnkStruct_0229b700 *);
}
extern const PMF data_ov131_0229b880;
extern const PMF data_ov131_0229b8a8;
extern const PMF data_ov131_0229b8d8;
extern const PMF data_ov131_0229b8d0;
extern "C" int func_ov131_0229b700(UnkStruct_0229b700 *this_ptr)
{
    static PMF pmf_table[4];
    static unsigned int initialized = 0;
    if (!(initialized & 1)) {
        pmf_table[0] = data_ov131_0229b880;
        pmf_table[1] = data_ov131_0229b8a8;
        pmf_table[2] = data_ov131_0229b8d8;
        pmf_table[3] = data_ov131_0229b8d0;
        initialized |= 1;
    }
    func_ov131_0229b474(this_ptr);
    (this_ptr->*pmf_table[this_ptr->selector])();
    func_ov131_0229b43c(this_ptr);
    return 1;
}
