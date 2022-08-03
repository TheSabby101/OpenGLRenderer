#include "Query.h"



Query::Query()
{
	//Test = 0;
	//any_samples_passed = 0;
	glDeleteQueries(1, *&Test);
	glGenQueries(1, *&Test);
}

Query::~Query()
{
	glDeleteQueries(1, *&Test);
}

void Query::GenQueries()
{
	if (any_samples_passed)
	glGenQueries(1, *&Test);
}

std::future<int>* Query::Begin()
{
	if (any_samples_passed)
		glGenQueries(1, *&Test);
	glBeginQuery(GL_SAMPLES_PASSED, *Test);
	std::future<int>* i;
	return i;
}

std::future<int>* Query::End()
{

	glEndQuery(GL_SAMPLES_PASSED);
	glGetQueryiv(GL_SAMPLES_PASSED, GL_QUERY_RESULT_AVAILABLE, *&any_samples_passed);
	//glGetQueryObjectiv(Test, GL_QUERY_RESULT_AVAILABLE, &any_samples_passed);
	std::future<int>* i;
	return i;
}
