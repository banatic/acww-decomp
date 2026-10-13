/* func_0209e6ec @ 0x0209e6ec, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0209e6ec;
typedef void (UnkStruct_0209e6ec::*PMF)();

extern PMF data_020e367c;
extern PMF data_020e3654;
extern PMF data_020e366c;
extern PMF data_020e3664;
extern PMF data_020e3684;
extern PMF data_020e3674;
extern PMF data_020e365c;

extern "C" void func_0209e6ec(UnkStruct_0209e6ec *self, int idx)
{
    static PMF tbl[7] = {data_020e367c, data_020e3654, data_020e366c, data_020e3664,
                         data_020e3684, data_020e3674, data_020e365c};
    (self->*tbl[idx])();
}
