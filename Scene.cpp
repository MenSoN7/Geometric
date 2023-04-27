
#include "Scene.h"
#include "SceneElement.h"

void Scene::AddElement(SceneElement& el)
{
	elements.push_back(std::shared_ptr<SceneElement>(&el));
}

void Scene::Write(std::ostream& out) const
{
	out << elements.size() << std::endl;
	for (const auto& i : elements)
	{
		i->Write(out);
		out << std::endl;
	}

}

void Scene::Read(std::istream& in)
{
	int size = 0;
	in >> size;

	for (int i = 0; i < size; ++i)
	{
		ReadBody(in, ReadId(in));
	}
}

SceneTypeId Scene::ReadId(std::istream& in)
{
	int id = -1;
	in >> id;
	return static_cast<SceneTypeId>(id);
}


void Scene::ReadBody(std::istream& in, SceneTypeId id)
{
	Point p;
	Polyline pl;
	Line l;
	Ellipse el;

	switch (id) {
	case SceneTypeId::Point:
		p.ReadSpecial(in);
		AddElement(*new Point(p));
		break;
	case SceneTypeId::Line:
		l.ReadSpecial(in);
		AddElement(*new Line(l));
		break;
	case SceneTypeId::Ellipse:
		el.ReadSpecial(in);
		AddElement(*new Ellipse(el));
		break;
	case SceneTypeId::Polyline:
		pl.ReadSpecial(in);
		AddElement(*new Polyline(pl));
		break;
	default:
		break;
	}
}


std::shared_ptr<SceneElement> Scene::Iterator()
{
	if (!elements.empty())
		return elements[idx];

	return (nullptr);
}



int Scene::first()
{
	if (elements.empty())
		return 0;
	idx = 0;
	return 1;
}


int Scene::next()
{
	if (!isDone())
	{
		++idx;
		return 1;
	}

	return 0;
}



bool Scene::isDone()
{
	return idx == elements.size();
}


