#include "pch.h"
#include "CppUnitTest.h"
#include "../Enigma_and_Bombe/Driver.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
/*
* Example Test Method:
	TEST_METHOD(TestClassInit)
	{
		std::string name = "Bill";
		MyClass mc(name);
		Assert::AreEqual(name, mc.GetName());
	}
*/
namespace EnigmaandBombeTest
{
	TEST_CLASS(EnigmaandBombeTest)
	{
	public:
		// Unit Tests for Rotors
		TEST_METHOD(Testmethod1)
		{
			Rotor rotor1;
			//Rotor rotor2(1, &rotor1 );
			Assert::AreEqual(rotor1.getNotch(), 0);
			//Assert::AreEqual(rotor2.getNotch(), 1);
		}
		// Unit Tests for Reflector
		TEST_METHOD(Testmethod2)
		{
		}
		// Unit Tests for Plugboard
		TEST_METHOD(Testmethod3)
		{
			Plugboard* p1 = new Plugboard();
			int test = 1;
			int test_swap[10] = { 9, 7, 10, 15, 17, 20, 25, 18, 22, 11 };
			int test_connections[26] = { 1, 2, 3, 4, 5, 6, 9, 8, 7, 10, 15,
			22, 13, 14, 15, 10, 17, 20, 25, 20, 17, 22, 11, 24, 25, 18 };
			p1->setPlugPos(test_swap);
			if (p1->getConnections() == test_connections) {
				test = 0;
			}
			Assert::AreEqual(test, 0);
		}
	};
}
