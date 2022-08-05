#include "Query.h"



Query::Query()
{

	//Test = 0;
	//any_samples_passed = 0;

	Test[2] = 0;
	glDeleteQueries(3, Test);
	glGenQueries(3, Test);
	Begin();
}

Query::~Query()
{
	//End();
	glDeleteQueries(3, Test);
}

void Query::GenQueries()
{
	if (!any_samples_passed)
	glGenQueries(3, Test);
}

bool Query::Begin()
{
	if (!any_samples_passed)
		glGenQueries(3, Test);
	glBeginQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, Test[0]);
	glBeginQuery(GL_SAMPLES_PASSED, Test[1]);
	glBeginQuery(GL_ANY_SAMPLES_PASSED, Test[2]);

	return any_samples_passed;
}

bool Query::End()
{

	glEndQuery(GL_SAMPLES_PASSED);
	glEndQuery(GL_ANY_SAMPLES_PASSED);
	glEndQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE);
	glGetQueryiv(GL_SAMPLES_PASSED, GL_QUERY_RESULT_AVAILABLE, &any_samples_passed);
	glGetQueryiv(GL_ANY_SAMPLES_PASSED, GL_QUERY_RESULT_AVAILABLE, &any_samples_passed);
	glGetQueryiv(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, GL_QUERY_RESULT_AVAILABLE, &any_samples_passed);
	//glGetQueryObjectiv(Test, GL_QUERY_RESULT_AVAILABLE, &any_samples_passed);
	
	if (any_samples_passed >= 1)
	{
		return any_samples_passed;
	}
	else {
		return 0;
	}
}
