#include <fstream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/io/svg/svg_mapper.hpp>
#include <boost/assign/list_of.hpp>

template <class Geometry1, class Geometry2>
void save_svg(const std::string& filename, const Geometry1& a, const Geometry2& b)
{
	std::ofstream svg(filename.c_str());
	typedef typename boost::range_value<Geometry1>::type point_type;
    boost::geometry::svg_mapper<point_type> mapper(svg, 400, 400);

    mapper.add(a);
    mapper.add(b);

    mapper.map(a, "fill-opacity:0.5;fill:rgb(153,204,0);stroke:rgb(153,204,0);stroke-width:2");
    mapper.map(b, "opacity:0.8;fill:none;stroke:rgb(255,128,0);stroke-width:4;stroke-dasharray:1,7;stroke-linecap:round");
}

namespace bg = boost::geometry;

typedef bg::model::d2::point_xy<double> point;
typedef bg::model::linestring<point> linestring;

int main()
{
    const linestring line = boost::assign::list_of<point>
        (3, 3)
        (3.8, 4)
        (6, 6)
        (4, 9)
        (5, 8)
        (7, 7)
        ;

    linestring result;
    bg::simplify(line, result, 0.5);

	save_svg("simplify.svg", line, result);
}

