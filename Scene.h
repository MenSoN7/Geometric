#pragma once

#include "figure.h"
#include "SceneElement.h"
#include <stdint.h>
#include <memory>


class Scene {
private:

	std::vector<std::shared_ptr<SceneElement>> elements;
	int idx{ 0 };

public:
	void AddElement(SceneElement& el);


	void Write(std::ostream& out) const;
	
	void Read(std::istream& in);
	
	SceneTypeId ReadId(std::istream& in);
	
	void ReadBody(std::istream& in, SceneTypeId id);
	
	std::shared_ptr<SceneElement> Iterator();

	int first();

	int next();

	bool isDone();


	//std::vector<std::shared_ptr<SceneElement>>::iterator first = elements.begin() ;


};

