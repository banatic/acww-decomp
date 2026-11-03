/* chat_scene_2: 2 functions, module ov111
 * mwccarm 1.2/base -O4,s
 * func_ov111_0229f0ec @ 0x0229f0ec, 0x20 bytes, Thumb
 * func_ov111_0229f0cc @ 0x0229f0cc, 0x20 bytes, Thumb
 */

extern void func_ov002_0220a1dc(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_0220a164(void *);

void func_ov111_0229f0ec(void *param)
{
    func_ov002_0220a1dc((char *) param + 0x3d38);
    func_ov002_02208098((void *) (param), 5);
}

void func_ov111_0229f0cc(void *self)
{
    func_ov002_0220a164((char *) self + 0x3d38);
    func_ov002_02208098((void *) (self), 7);
}
