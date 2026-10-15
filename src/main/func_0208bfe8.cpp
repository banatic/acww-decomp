/* func_0208bfe8 @ 0x0208bfe8, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0208bfe8 {
  public:
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
};

extern "C" int func_0208c658(void *);
extern "C" void func_0208be44(void *);

extern "C" void func_0208bfe8(UnkStruct_0208bfe8 *obj)
{
    obj->vf3();
    func_0208c658((char *) obj + 0x28);
    func_0208be44(obj);
}
