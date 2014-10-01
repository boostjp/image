#include <fstream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/assign/list_of.hpp>

namespace bg = boost::geometry;
namespace trans = bg::strategy::transform;

typedef bg::model::d2::point_xy<double> point;
typedef bg::model::polygon<point> polygon;

template <class Geometry1, class Geometry2>
void save_svg(const std::string& filename, const Geometry1& a, const Geometry2& b)
{
    std::ofstream svg(filename.c_str());
    typedef typename boost::geometry::point_type<Geometry1>::type point_type;
    boost::geometry::svg_mapper<point_type> mapper(svg, 240, 480);

    mapper.add(a);
    mapper.add(b);

    mapper.map(a, "fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:2");
    mapper.map(b, "opacity:0.8;fill:none;stroke:rgb(255,128,0);stroke-width:4;stroke-dasharray:1,7;stroke-linecap:round");
}

int main()
{
    polygon poly;
    bg::exterior_ring(poly) = boost::assign::list_of<point>
        (0, 0)
        (3, 3)
        (3, 0)
        (0, 0)
        ;

    trans::rotate_transformer<bg::degree, double, 2, 2> translate(90.0);

    polygon result;
    bg::transform(poly, result, translate);

    save_svg("rotate.svg", poly, result);
}

