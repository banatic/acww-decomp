/* map_menu_scene_6: 2 functions, module ov118
 * mwccarm 1.2/base -O4,s
 * func_ov118_0229c9c0 @ 0x0229c9c0, 0x20 bytes, Thumb
 * func_ov118_0229c9a4 @ 0x0229c9a4, 0x1a bytes, Thumb
 */

extern void func_ov118_0229c098(void *p);
extern void func_ov002_02208090(void *p, int n);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);
extern int func_020ee45c(int);
extern unsigned char func_ov090_0229936c(void *);
extern void func_ov118_0229c078(int);

int func_ov118_0229c9c0(void *p)
{
    func_ov118_0229c098(p);
    func_ov002_02208090(p, 0);
    func_ov002_022080a0(p, 1);
    return 1;
}

int func_ov118_0229c9a4(int arg)
{
    func_ov090_0229936c((void *) func_020ee45c(arg));
    func_ov118_0229c078(arg);
    return 1;
}
