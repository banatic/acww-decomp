/* func_020b3504 @ 0x020b3504, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" int func_02057a50(int, int);

class UnkStruct_020b3504 {
  public:
    virtual int func(int i);
    signed char data[3];
};

extern "C" void func_020b3504(UnkStruct_020b3504 *obj, int arg1)
{
    unsigned int i;
    for (i = 0; i < 3; i++) {
        if (obj->func(i) != 0) {
            int r = func_02057a50(arg1, obj->func(i));
            if (r != -1) {
                obj->data[i] = r;
            } else {
                obj->data[i] = -1;
            }
        }
    }
}
