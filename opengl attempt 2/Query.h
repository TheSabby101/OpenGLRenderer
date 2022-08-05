#pragma once
#include "Header.h"
class Query
{
  

	
public:
	

	static GLuint Test[2];
	//GLuint Test;
	static GLint any_samples_passed;
	 Query();
	 ~Query();
	void GenQueries();
	bool Begin();
	bool End();





};

