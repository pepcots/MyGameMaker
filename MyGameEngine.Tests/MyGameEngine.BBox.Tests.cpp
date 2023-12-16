#include <CppUnitTest.h>
#include "../MyGameEngine/BBox.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyGameEngineTests
{
	TEST_CLASS(BBoxTests)
	{
	public:
		
		TEST_METHOD(AABBoxIsWellComputedFromOBBox)
		{
			OBBox obbox;
			obbox.a = vec3(0, 0, 1);
			obbox.b = vec3(1, 0, 1);
			obbox.c = vec3(1, 1, 1);
			obbox.d = vec3(0, 1, 1);
			obbox.e = vec3(0, 0, 0);
			obbox.f = vec3(1, 0, 0);
			obbox.g = vec3(1, 1, 0);
			obbox.h = vec3(0, 1, 0);
			AABBox aabbox = obbox.AABB();

			Assert::IsTrue(aabbox.a()==vec3(0, 0, 1));
		}
	};
}
