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
		Rotor rotor1;
		TEST_METHOD(TestNotch)
		{
			Assert::AreEqual(rotor1.getNotch(), 0);
		}

		TEST_METHOD(TestNotch2)
		{
			Rotor rotor2(5, &rotor1);
			Assert::AreEqual(rotor2.getNotch(), 5);


		}
		//TEST_METHOD(TestReference)
		//{
		//	Rotor rotor3(5, &rotor1);
		//	Assert::AreSame(rotor3.getReference(), &rotor1);
		//}

		TEST_METHOD(TestPosition)
		{
			Assert::AreEqual(rotor1.getPosition(), 0);
		}

		TEST_METHOD(TestGetScramblePos)
		{
			Assert::AreEqual(rotor1.getScramblePos(0), 20);
		}

		TEST_METHOD(TestRotate)
		{
			rotor1.rotate();
			Assert::AreEqual(rotor1.getPosition(), 1);
		}
	};
}
