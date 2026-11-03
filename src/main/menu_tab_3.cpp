/* menu_tab_3: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0208bfe8 @ 0x0208bfe8, 0x1e bytes, Thumb
 * func_0208bfd0 @ 0x0208bfd0, 0x18 bytes, Thumb
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

class UnkStruct_0208bfd0 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    char pad_04[0x28 - 4];
    char sub[4];
};

extern "C" int func_0208c638(void *sub);

extern "C" void func_0208bfe8(UnkStruct_0208bfe8 *obj)
{
    obj->vf3();
    func_0208c658((char *) obj + 0x28);
    func_0208be44(obj);
}

extern "C" void func_0208bfd0(UnkStruct_0208bfd0 *self)
{
    self->v2();
    func_0208c638(self->sub);
}
