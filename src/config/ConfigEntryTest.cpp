/*
 * ConfigEntryTest.cpp
 *
 *  Created on: 29 Mar 2011
 *      Author: "SevenMachines <SevenMachines@yahoo.co.uk>"
 */

#include "ConfigEntryTest.h"
#include "config/ConfigEntry.h"
#include "common/Containers.h"

using namespace cryomesh;

namespace cryomesh {

namespace config {

void ConfigEntryTest::runSuite() {
	cute::suite s;
	s.push_back(CUTE(ConfigEntryTest::testParseEntry));
	s.push_back(CUTE(ConfigEntryTest::testGetIntegerFormattedOptions));
	s.push_back(CUTE(ConfigEntryTest::testToIntegerMultipleValues));
	s.push_back(CUTE(ConfigEntryTest::testTokenizeMultipleValueString));
	cute::ide_listener lis;
	cute::makeRunner(lis)(s, "ConfigEntryTest");
}

void ConfigEntryTest::testParseEntry() {
	{
		std::string teststring1 = "command option1=1 option2=2 option3=3 option4=\"4 5 6\" ";
		ConfigEntry confentry(teststring1);
#ifdef CONFIGENTRYTEST_DEBUG
		std::cout<<"ConfigEntryTest::testParseEntry: "<<confentry<<std::endl;
#endif
		ASSERT_EQUAL(teststring1, confentry.getRawEntry());
		ASSERT_EQUAL("command", confentry.getCommand());
		ASSERT_EQUAL("1", confentry.getOptionValue("option1"));
		ASSERT_EQUAL("2", confentry.getOptionValue("option2"));
		ASSERT_EQUAL("3", confentry.getOptionValue("option3"));
		ASSERT_EQUAL("4 5 6", confentry.getOptionValue("option4"));


	}

	// test error
	{
		std::string teststring1 = "autoconnect-inputs ids=\"1 2\"";
				ConfigEntry confentry(teststring1);

				std::cout<<"ConfigEntryTest::testParseEntry: "<<confentry<<std::endl;
				ASSERT_EQUAL(teststring1, confentry.getRawEntry());
				ASSERT_EQUAL("autoconnect-inputs", confentry.getCommand());
				ASSERT_EQUAL("1 2", confentry.getOptionValue("ids"));

	}
}

void ConfigEntryTest::testGetIntegerFormattedOptions() {
	std::string entr_str = "command option1=1 option2=2 option3=3";
	ConfigEntry conf_entry(entr_str);
	std::map<std::string, int> intmap = conf_entry.getIntegerFormattedOptions();

	// forall in intmap
	{
		std::map<std::string, int>::const_iterator it_intmap = intmap.begin();
		const std::map<std::string, int>::const_iterator it_intmap_end = intmap.end();
		while (it_intmap != it_intmap_end) {
			std::string opt = it_intmap->first;
			int val = it_intmap->second;

			if (opt == "option1") {
				ASSERT_EQUAL(1, val);
			} else if (opt == "option2") {
				ASSERT_EQUAL(2, val);
			} else if (opt == "option3") {
				ASSERT_EQUAL(3, val);
			} else {
				std::cout << "ConfigEntryTest::testGetIntegerFormattedOptions: " << "'" << opt << "'" << ":" << "'"
						<< val << "'" << std::endl;
				ASSERTM("Unknown option!", false);
			}
			++it_intmap;
		}
	}
}

void ConfigEntryTest::testToIntegerMultipleValues() {

	std::vector<std::string> vals ({"1", "2", "3"});
	std::vector<int> expected = {1, 2, 3};
	std::vector<int> actual = ConfigEntry::toIntegerMultipleValues(vals);
	ASSERT(common::Containers::compare(actual, expected));
}
void ConfigEntryTest::testTokenizeMultipleValueString() {
	std::string val_string= "1 a 3";
		std::vector<std::string> expected ({"1", "a", "3"});
		std::vector<std::string> actual = ConfigEntry::tokenizeMultipleValueString(val_string);
		ASSERT(common::Containers::compare(actual, expected));
}
}//NAMESPACE

}//NAMESPACE
