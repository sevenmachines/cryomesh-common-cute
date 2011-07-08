#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

//spacial
#include "spacial/SphericalPointTest.h"
#include "spacial/PointTest.h"
#include "spacial/BoundingBoxTest.h"
#include "spacial/ActivityGridTest.h"
#include "spacial/GridContainerTest.h"

// common
#include "common/SimpleCollectionTest.h"
#include "common/MiscTest.h"
#include "common/MathsTest.h"
#include "common/ContainersTest.h"
#include "common/KeyStoreTest.h"

//config
#include "config/ConfigEntryTest.h"
#include "config/ConfigTranslatorTest.h"

using namespace cryomesh;

void runSpacialSuite() {
	spacial::SphericalPointTest::runSuite();
	spacial::PointTest::runSuite();
	spacial::BoundingBoxTest::runSuite();
	spacial::ActivityGridTest::runSuite();
//	spacial::GridContainerTest::runSuite();
}
void runCommonSuite() {
	common::SimpleCollectionTest::runSuite();
	common::MiscTest::runSuite();
	common::MathsTest::runSuite();
	common::ContainersTest::runSuite();
	common::KeyStoreTest::runSuite();
}

void runConfigSuite() {
	config::ConfigEntryTest::runSuite();
	config::ConfigTranslatorTest::runSuite();
}

int main() {
	runCommonSuite();
	runConfigSuite();
	runSpacialSuite();
	return 0;
}

