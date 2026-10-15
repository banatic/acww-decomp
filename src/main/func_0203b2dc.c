/* func_0203b2dc @ 0x0203b2dc, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ac78(void);
extern void func_0203be6c(int p);
extern void func_01ffcbb0(void *buf, int p);
extern int func_0203c57c(int p);
extern int func_0203c568(int p);
extern int func_0203c548(int p);
extern void func_0203bd84(int p, void *buf, int a, int b, int c);

void func_0203b2dc(int p)
{
    unsigned char buffer[8];
    func_0203ac78();
    func_0203be6c(p);
    func_01ffcbb0(buffer, p);
    func_0203bd84(p, buffer, func_0203c57c(p), func_0203c568(p), func_0203c548(p));
}
