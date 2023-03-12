#include "main.h"

void simulate(string filename, restaurant* r);

int main(int argc, char* argv[]) {

    restaurant* r = new restaurant();
    string fileName = "test/test.txt";

    //initialize table with ID, name and age
    for (int i = 1; i <= MAXSIZE; i++)
    {
        r->recentTable = r->insert(r->recentTable,i,"",0);
    }

    simulate(fileName,r);
    delete r;

    return 0;
}
