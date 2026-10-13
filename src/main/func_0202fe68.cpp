/* func_0202fe68 @ 0x0202fe68, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class Class {
  public:
    virtual int vf0(void *arg2, int arg3, int arg4);
    virtual int vf1(void *arg2, int arg3, int arg4);
    virtual int vf2(void *arg2, int arg3, int arg4);
};

extern "C" int func_0202fe68(Class *obj, void *arg2, int arg3, int arg4)
{
    int result = 0;
    if (obj->vf1(arg2, arg3, arg4)) {
        result = 1;
    }
    if (obj->vf0(arg2, arg3, arg4)) {
        result = 1;
    }
    if (obj->vf2(arg2, arg3, arg4)) {
        result = 1;
    }
    return result;
}
