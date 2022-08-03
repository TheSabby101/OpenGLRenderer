#pragma once
#include "Header.h"
class Query
{
  


public:
	inline static GLuint* Test;
	inline static GLint* any_samples_passed;
	 Query();
	 ~Query();
	static void GenQueries();
	static std::future<int>* Begin();
	static std::future<int>* End();





};

