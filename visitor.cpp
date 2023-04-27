#include "visitor.h"

void LengthSumVisitor::Visit(Line& l) {
	total_length += std::hypot(l.GetFirstPoint().GetX() - l.GetSecondPoint().GetX(),
		l.GetFirstPoint().GetY() - l.GetSecondPoint().GetY());
}


void LengthSumVisitor::Visit(Polyline& pl) 
{

	for (int i = 0; i < pl.GetSize() - 1; ++i)
		total_length += std::hypot(pl.GetPoints(i).GetX() - pl.GetPoints(i + 1).GetX(),
			pl.GetPoints(i).GetY() - pl.GetPoints(i + 1).GetY());
}


void LengthSumVisitor::Visit(Ellipse& el)  {

	double d_t = (el.GetTMax() - el.GetTMin()) / 100;
	Point p;
	Point pp;
	for (double t = el.GetTMin(); t <= el.GetTMax(); t += d_t)
	{
		p = el.Formula(t);
		pp = el.Formula(t + d_t);
		total_length += std::hypot(p.GetX() - pp.GetX(), p.GetY() - pp.GetY());
	}


}
