/*
euler6.h
April 2, 2024
Contributors:
Justin Jensen
*/

#pragma once

namespace hxm
{
    class euler6
    {
    // Defines
    private:
    protected:
    public:
        // TODO: evaluation order (default to XY, ZX, XW, YZ, WY, ZW)
    
    // Members
    private:
    protected:
    public:
        float xy;
        float zx;
        float xw;
        float yz;
        float wy;
        float zw;
    
    // Functions
    private:
    protected:
    public:
        euler6(float XY, float ZX, float XW, float YZ, float WY, float ZW) : xy(XY), zx(ZX), xw(XW), yz(YZ), wy(WY), zw(ZW) {}
        euler6(float XW, float WY, float ZW) : xy(0.0f), zx(0.0f), xw(XW), yz(0.0f), wy(WY), zw(ZW) {}
        euler6() : xy(0.0f), zx(0.0f), xw(0.0f), yz(0.0f), wy(0.0f), zw(0.0f) {}
    };
}