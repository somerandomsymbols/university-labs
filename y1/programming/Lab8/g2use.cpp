#include "g2.h"
#include "g2use.h"

void doMagic(std::string si, std::string so)
{
    double ax, ay, bx, by, cx, cy, dx, dy;
    std::ifstream fi;
    std::ofstream fo;
    fi.open(si);
    fo.open(so);

    while (fi >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy)
    {
        try
        {
            Polygon p({Point(ax, ay), Point(bx, by), Point(cx, cy), Point(dx, dy)});
            fo << '(' << ax << ", " << ay << "), (" << bx << ", " << by << "), (" << cx << ", " << cy << "), (" << dx << ", " << dy << "); ";

            if (p.getVector(0)*p.getVector(0) == p.getVector(2)*p.getVector(2) && p.getVector(1)*p.getVector(1) == p.getVector(3)*p.getVector(3) && (~p.getSegment(0) * ~p.getSegment(2) == abs(p.getVector(0) * p.getVector(2))) && (~p.getSegment(1) * ~p.getSegment(3) == abs(p.getVector(1) * p.getVector(3))))
            {
                fo << "Is a Rhombus, possibly degenerated into straight line\n";
            }
            else
            {
                fo << "Is not a Rhombus\n";
            }
        }
        catch (std::runtime_error e)
        {
            std::cout << e.what();
        }
    }

    fi.close();
    fo.close();
}
