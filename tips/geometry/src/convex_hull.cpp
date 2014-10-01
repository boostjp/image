#include <fstream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/assign/list_of.hpp>

template <class Geometry1, class Geometry2>
void save_svg(const std::string& filename, const Geometry1& a, const Geometry2& b)
{
    std::ofstream svg(filename.c_str());
    typedef typename boost::geometry::point_type<Geometry1>::type point_type;
    boost::geometry::svg_mapper<point_type> mapper(svg, 400, 270);

    mapper.add(a);
    mapper.add(b);

    mapper.map(a, "fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:2");
    mapper.map(b, "opacity:0.8;fill:none;stroke:rgb(255,128,0);stroke-width:4;stroke-dasharray:1,7;stroke-linecap:round");
}

int main()
{
    namespace bg = boost::geometry;

    typedef bg::model::d2::point_xy<double> point;
    typedef bg::model::polygon<point> polygon;

    polygon poly;
    bg::exterior_ring(poly) = boost::assign::list_of<point>
        (2.0, 1.3)
        (2.4, 1.7)
        (3.6, 1.2)
        (4.6, 1.6)
        (4.1, 3.0)
        (5.3, 2.8)
        (5.4, 1.2)
        (4.9, 0.8)
        (3.6, 0.7)
        (2.0, 1.3)
        ;

    polygon hull;
    bg::convex_hull(poly, hull);
       
    save_svg("convex_hull.svg", poly, hull);
}
