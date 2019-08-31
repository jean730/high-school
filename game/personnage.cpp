class Perso {
public:
    void die(Music& diesound, int winh)
    {
        diesound.play();
        dead = 1;
        lose = 5;
        yVel = -12;
    }
    void respawn(int spriw, int sprih, int winh)
    {
        x = spriw * spawnx;
        y = winh - sprih*spawny - (ySize / 2) * scale;
        dead = 0;
    }
    void setspawn(int sx, int sy)
    {
        spawnx=sx;
        spawny=sy;
    }
    double dead = 0;
    double lose = 0;
    double x = 0;
    double y = 16;
    int spawnx = 2;
    int spawny = 2;
    double scale = 0.5;
    double xSize = 176;
    double ySize = 168;
    std::string sprite = "Textures/perso.png";
    double xVel = 0;
    double yVel = 0;
    double zoom = 0;
};

