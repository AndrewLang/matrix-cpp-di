#include "gtest/gtest.h"
#include "pipeline/PipelineContext.h"


using namespace std;

namespace Matrix
{
	TEST(PipelineContextTests, Constructor) {
		PipelineContext context;
	}

	TEST(PipelineContextTests, Abort) {
		PipelineContext context;

		ASSERT_FALSE(context.isAborted());

		context.abort();

		ASSERT_TRUE(context.isAborted());
	}

	TEST(PipelineContextTests, GetSetProperties) {
		PipelineContext context;

		context.setProperty<string>("name", "pxi")
			.setProperty<int>("version", 1);

		ASSERT_EQ("pxi", context.getProperty<string>("name"));
		ASSERT_EQ(1, context.getProperty<int>("version"));
	}	

	TEST(PipelineContextTests, Copy) {
		PipelineContext context;

		context.setProperty<string>("name", "pxi")
			.setProperty<int>("version", 1);

		PipelineContext copied(context);
		

		ASSERT_EQ("pxi", copied.getProperty<string>("name"));
		ASSERT_EQ(1, copied.getProperty<int>("version"));
	}
}