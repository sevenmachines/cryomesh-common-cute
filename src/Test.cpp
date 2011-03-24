#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

//spacial
#include "spacial/SphericalPointTest.h"
#include "spacial/PointTest.h"


// common
#include "common/SimpleCollectionTest.h"
#include "common/MiscTest.h"
#include "common/MathsTest.h"
#include "common/ContainersTest.h"
#include "common/KeyStoreTest.h"

using namespace cryomesh;

void runSpacialSuite() {
	spacial::SphericalPointTest::runSuite();
	spacial::PointTest::runSuite();
}
void runCommonSuite() {
	common::SimpleCollectionTest::runSuite();
	common::MiscTest::runSuite();
	common::MathsTest::runSuite();
	common::ContainersTest::runSuite();
	common::KeyStoreTest::runSuite();
}


int main() {
	runCommonSuite();
	runSpacialSuite();
	return 0;
}

