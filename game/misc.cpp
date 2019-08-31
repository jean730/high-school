using namespace sf;
bool collide(double x1, double y1, double w1, double h1, double x2, double y2,
    double w2, double h2)
{
    return !(x1 > x2 + w2 - 1 | y1 > y2 + h2 - 1 | x2 > x1 + w1 - 1 | y2 > y1 + h1 - 1);
}
string stbool(bool boolean)
{
    if (boolean) {
        return "on";
    }
    else {
        return "off";
    }
}


IntRect tileRect(int a, int state)
{
    int b = 0;
    if (a <= 64) {
        while (a > 7) {
            a -= 8;
            b++;
        }
    }
    else if (a == 65) {
        switch (state) {
        case 1:
            a = 4;
            b = 6;
            break;
        case 2:
            a = 5;
            b = 7;
            break;
        case 3:
            a = 5;
            b = 6;
            break;
        case 4:
            a = 4;
            b = 7;
            break;
        case 5:
            a = 5;
            b = 6;
            break;
        case 6:
            a = 5;
            b = 7;
            break;
        }
    }
    IntRect rect(a * 16, b * 16, 16, 16);
    return rect;
}
