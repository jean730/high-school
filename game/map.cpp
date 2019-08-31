
using namespace std;
class Map1 {
public:
    Map1(string mapfile)
    {
        set(mapfile);
    }

    void set(string mapfile)
    {
        mapFile = mapfile;
        ifstream fluxi(mapfile);
        getline(fluxi, name);
        getline(fluxi, temp);
        spawnx = std::stoi(temp);
        getline(fluxi, temp);
        spawny = std::stoi(temp);
        for (int i = 0; i < 7; i++) {
            getline(fluxi, ligne[6 - i]);
            for (int j = 0; j < 450; j += 3) {
                temp = "";
                temp += ligne[6 - i][j];
                temp += ligne[6 - i][j + 1];

                map[i][j / 3] = std::stoi(temp);
            }
        }

        for (int i = 0; i < 7; i++) {
            getline(fluxi, ligne[6 - i]);
            for (int j = 0; j < 450; j += 3) {
                temp = "";
                temp += ligne[6 - i][j];
                temp += ligne[6 - i][j + 1];
                mapCollide[i][j / 3] = std::stoi(temp);
            }
        }
    }

    string ligne[7];
    string temp;
    std::string TileSet = "Textures/tileset.png";
    int tilesetHeight = 128;
    int tilesetWidth = 128;
    int tileHeight = 16;
    int tileWidth = 16;
    int Lines = 7;
    int Columns = 150;
    int spawnx;
    int spawny;
    int map[7][150]{};
    int mapCollide[7][150]{};
    string mapFile;
    string name;
    int scale = 6;
};

void printMap(Map1& map)
{
    ofstream fluxo(map.mapFile);
    fluxo << map.name << "\n";
    fluxo << map.spawnx << "\n";
    fluxo << map.spawny << "\n";
    for (int i = 0; i < map.Lines; i++) {

        for (int j = 0; j < map.Columns; j++) {
            if (map.map[i][j] < 10) {
                fluxo << "0";
            }
            fluxo << map.map[i][j];

            if (j < map.Columns - 1) {
                fluxo << ",";
            }
        }

        if (i < map.Lines - 1) {
        }
        fluxo << "\n";
    }

    for (int i = 0; i < map.Lines; i++) {

        for (int j = 0; j < map.Columns; j++) {
            if (map.mapCollide[i][j] < 10) {
                fluxo << "0";
            }
            fluxo << map.mapCollide[i][j];

            if (j < map.Columns - 1) {
                fluxo << ",";
            }
        }

        if (i < map.Lines - 1) {
        }
        fluxo << "\n";
    }
}
