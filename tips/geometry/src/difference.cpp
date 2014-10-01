#include <fstream>
#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/assign/list_of.hpp>

template <class Geometry1, class Geometry2, class Range>
void save_svg(const std::string& filename, const Geometry1& a, const Geometry2& b, const Range& range)
{
    std::ofstream svg(filename.c_str());
    typedef typename boost::geometry::point_type<Geometry1>::type point_type;
    boost::geometry::svg_mapper<point_type> mapper(svg, 400, 400);

    mapper.add(a);
    mapper.add(b);

    mapper.map(a, "fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:2");
    mapper.map(b, "fill-opacity:0.3;fill:rgb(51,51,153);stroke:rgb(51,51,153);stroke-width:2");

    int i = 0;
    for (const auto& g : range) {
        mapper.map(g, "opacity:0.8;fill:none;stroke:rgb(255,128,0);stroke-width:4;stroke-dasharray:1,7;stroke-linecap:round");
        std::ostringstream out;
        out << i++;
        mapper.text(boost::geometry::return_centroid<point_type>(g), out.str(),
                    "fill:rgb(0,0,0);font-family:Arial;font-size:10px");
    }
}

namespace bg = boost::geometry;

typedef bg::model::d2::point_xy<double> point;
typedef bg::model::polygon<point> polygon;
typedef bg::model::box<point> box;

int main()
{
    const box bx(point(2, 0), point(6, 4.5));

    polygon poly;
    bg::exterior_ring(poly) = boost::assign::list_of<point>
        (1, 1)
        (5, 5)
        (5, 1)
        (1, 1)
        ;

    // bx - poly
    std::vector<polygon> out;
    bg::difference(bx, poly, out);

    save_svg("difference.svg", bx, poly, out);
}
